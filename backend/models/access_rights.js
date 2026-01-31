const db = require('../db');

//List all access rights
const accessRights = {
  getAll: function(callback) {
    return db.query('SELECT * FROM access_rights', callback);
  },

//List access rights by customer
  getByCustomer: function(customer_id, callback) {
    return db.query(
      'SELECT * FROM access_rights WHERE customer_customer_id=?',
      [customer_id],
      callback
    );
  },

//List access rights by account
  getByAccount: function(account_id, callback) {
    return db.query(
      'SELECT * FROM access_rights WHERE account_account_id=?',
      [account_id],
      callback
    );
  },

//Get one access right by customer and account
  getOne: function(customer_id, account_id, callback) {
    return db.query(
      'SELECT * FROM access_rights WHERE customer_customer_id=? AND account_account_id=?',
      [customer_id, account_id],
      callback
    );
  },

//Add new access right
  add: function(right, callback) {
    return db.query(
      'INSERT INTO access_rights (access, customer_customer_id, account_account_id) VALUES (?,?,?)',
      [right.access, right.customer_customer_id, right.account_account_id],
      callback
    );
  },

//Update access right
  update: function(customer_id, account_id, access, callback) {
    return db.query(
      'UPDATE access_rights SET access=? WHERE customer_customer_id=? AND account_account_id=?',
      [access, customer_id, account_id],
      callback
    );
  },
  
//Delete access right
  delete: function(customer_id, account_id, callback) {
    return db.query(
      'DELETE FROM access_rights WHERE customer_customer_id=? AND account_account_id=?',
      [customer_id, account_id],
      callback
    );
  }
};

module.exports = accessRights;
