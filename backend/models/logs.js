const db = require('../db');

const logs = {

  // GET all logs
  getAll: function (callback) {
    return db.query(
      `SELECT logs_id, time, event, amount, description, account_account_id
       FROM logs
       ORDER BY time DESC`,
      callback
    );
  },

  // GET one log
  getOne: function (logs_id, account_account_id, callback) {
    return db.query(
      `SELECT logs_id, time, event, amount, description, account_account_id
       FROM logs
       WHERE logs_id = ? AND account_account_id = ?`,
      [logs_id, account_account_id],
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

  // UPDATE log (harvinainen mutta mukana)
  update: function (logs_id, log, callback) {
    return db.query(
      `UPDATE logs
       SET event = ?, amount = ?, description = ?
       WHERE logs_id = ?`,
      [
        log.event,
        log.amount,
        log.description,
        logs_id
      ],
      callback
    );
  }
};

module.exports = logs;
