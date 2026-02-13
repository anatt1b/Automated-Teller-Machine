const db = require('../db');

const logs = {

  //  create new log 
  create: function (
    account_id,
    type,
    amount,
    balance_before,
    balance_after,
    description,
    callback
  ) {
    return db.query(
      `INSERT INTO logs
       (account_id, type, amount, balance_before, balance_after, description)
       VALUES (?, ?, ?, ?, ?, ?)`,
      [
        account_id,
        type,
        amount,
        balance_before,
        balance_after,
        description
      ],
      callback
    );
  },

  //  get all logs from account
  getByAccount: function (account_id, callback) {
    return db.query(
      `SELECT log_id, type, amount, balance_before, balance_after,
              description, timestamp
       FROM logs
       WHERE account_id = ?
       ORDER BY timestamp DESC`,
      [account_id],
      callback
    );
  },

  //  get latest logs (10 or so)
  getLatestByAccount: function (account_id, limit, callback) {
    return db.query(
      `SELECT log_id, type, amount, balance_before, balance_after,
              description, timestamp
       FROM logs
       WHERE account_id = ?
       ORDER BY timestamp DESC
       LIMIT ?`,
      [account_id, Number(limit)],
      callback
    );
  },

  //  systemlog 
  createSystemLog: function (description, callback) {
    return db.query(
      `INSERT INTO logs
       (account_id, type, amount, description)
       VALUES (?, 'SYSTEM', 0, ?)`,
      [0, description],
      callback
    );
  },

  // ADD new log
  add: function (log, callback) {
    return db.query(
      `INSERT INTO logs
       (time, event, amount, description, account_account_id)
       VALUES (NOW(), ?, ?, ?, ?)`,
      [
        log.event,
        log.amount,
        log.description,
        log.account_account_id
      ],
      callback
    );
  },

  // DELETE log
  delete: function (logs_id, callback) {
    return db.query(
      `DELETE FROM logs
       WHERE logs_id = ?`,
      [logs_id],
      callback
    );
  },

 
};

module.exports = logs;
