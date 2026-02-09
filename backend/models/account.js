const db = require('../db');

const account = {
  // GET all accounts
  getAll: function (callback) {
    return db.query(
      `SELECT account_id, balance, open_date, credit_limit, customer_customer_id
       FROM account`,
      callback
    );
  },

  // GET one account
  getOne: function (account_id, customer_customer_id, callback) {
    return db.query(
      `SELECT account_id, balance, open_date, credit_limit, customer_customer_id
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
  }
};
module.exports = account;
