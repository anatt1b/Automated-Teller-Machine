const db = require('../db');

const logs = {

  create: function (
    account_id,
    event,
    amount,
    balance_before,
    balance_after,
    description,
    callback
  ) {
    return db.query(
      `INSERT INTO logs
       (time, event, amount, description,
        account_account_id, balance_before, balance_after)
       VALUES (NOW(), ?, ?, ?, ?, ?, ?)`,
      [
        event,
        amount,
        description,
        account_id,
        balance_before,
        balance_after
      ],
      callback
    );
  },

  getByAccount: function(account_id, callback) {
    return db.query(
      `SELECT logs_id, time, event,
              amount, description,
              balance_before, balance_after
       FROM logs
       WHERE account_account_id = ?
       ORDER BY time DESC`,
      [account_id],
      callback
    );
  },



 // GET all logs by account
  getByAccount: function(account_id, callback) {
    return db.query(
      `SELECT logs_id, time, event,
              amount, description,
              balance_before, balance_after
       FROM logs
       WHERE account_account_id = ?
       ORDER BY time DESC`,
      [account_id],
      callback
    );
  },

  // GET latest logs like 10 or so 
  getLatestByAccount: function(account_id, limit, callback) {
    return db.query(
      `SELECT logs_id, time, event,
              amount, description,
              balance_before, balance_after
       FROM logs
       WHERE account_account_id = ?
       ORDER BY time DESC
       LIMIT ?`,
      [account_id, Number(limit)],
      callback
    );
  },

  // SIMPLE add. Not really sure if needed but
  add: function (log, callback) {
    return db.query(
      `INSERT INTO logs
       (time, event, amount, description, account_account_id, balance_before, balance_after)
       VALUES (NOW(), ?, ?, ?, ?)`,
      [
        log.event,
        log.amount,
        log.description,
        log.account_account_id,
        log.balance_before,
        log.balance_after
      ],
      callback
    );
  },

  // DELETE log (admin)
  delete: function (logs_id, callback) {
    return db.query(
      `DELETE FROM logs
       WHERE logs_id = ?`,
      [logs_id],
      callback
    );
  }

};

module.exports = logs;
