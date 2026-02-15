const db = require('../db');
const Logs = require('./logs');

const account = {

  withdraw: function(account_id, amount, callback) {

    db.query(
      `SELECT balance, daily_withdraw_limit, daily_withdrawn
       FROM account
       WHERE account_id = ?`,
      [account_id],
      (err, result) => {

        if (err) return callback(err);
        if (!result[0])
          return callback(new Error("Account not found"));

        const balance = result[0].balance;
        const limit = result[0].daily_withdraw_limit;
        const withdrawn = result[0].daily_withdrawn;

        // balance check
        if (balance < amount)
          return callback(new Error("Insufficient balance"));

        //  daily limit check
        if (withdrawn + amount > limit)
          return callback(new Error("Daily withdraw limit exceeded"));

        const newBalance = balance - amount;
        const newDaily = withdrawn + amount;

        db.query(
          `UPDATE account
           SET balance = ?, daily_withdrawn = ?
           WHERE account_id = ?`,
          [newBalance, newDaily, account_id],
          (err2) => {

            if (err2) return callback(err2);

            //  Logging
            Logs.create(
              account_id,
              'DEBIT',
              amount,
              balance,
              newBalance,
              'DEBIT WITHDRAW'
            );

            callback(null, {
              balance: newBalance,
              daily_withdrawn: newDaily
            });
          }
        );
      }
    );
  }, 

 

  // GET all accounts
  getAll: function (callback) {
    return db.query(
      `SELECT account_id, balance, open_date, credit_limit, used_credit, daily_withdraw_limit, customer_customer_id
       FROM account`,
      callback
    );
  },

  // GET one account
  getOne: function (account_id, customer_customer_id, callback) {
    return db.query(
      `SELECT account_id, balance, open_date, credit_limit, used_credit, daily_withdraw_limit, customer_customer_id
       FROM account
       WHERE account_id = ? AND customer_customer_id = ?`,
      [account_id, customer_customer_id],
      callback
    );
  },

  // ADD new account
  add: function (account, callback) {
    return db.query(
      `INSERT INTO account
       (balance, open_date, credit_limit, customer_customer_id)
       VALUES (?, ?, ?, ?)`,
      [
        account.balance,
        account.open_date,
        account.credit_limit,
        account.customer_customer_id
      ],
      callback
    );
  },

  // DELETE account
  delete: function (account_id, customer_customer_id, callback) {
    return db.query(
      `DELETE FROM account
       WHERE account_id = ? AND customer_customer_id = ?`,
      [account_id, customer_customer_id],
      callback
    );
  },

  // UPDATE account
  update: function (account_id, customer_customer_id, account, callback) {
    return db.query(
      `UPDATE account
       SET balance = ?, open_date = ?, credit_limit = ?
       WHERE account_id = ? AND customer_customer_id = ?`,
      [
        account.balance,
        account.open_date,
        account.credit_limit,
        account_id,
        customer_customer_id
      ],
      callback
    );
  },

  // ADD used credit (when credit withdrawwal happens)
  addUsedCredit: function(account_id, amount, callback){
    return db.query(
      `UPDATE account
      SET used_credit = used_credit + ?
      Where account_id = ?`,
      [amount, account_id],
      callback
    );
  }
};

module.exports = account;
