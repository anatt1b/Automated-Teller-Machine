const db = require('../database');


const customer={
  getAll: function(callback) {
    return db.query('SELECT * FROM customer', callback);
  },
  getOne: function(customer_id, callback) {
    return db.query('SELECT * FROM customer WHERE customer_id=?', [customer_id], callback);
  },
  add: function(customer, callback) {
      return db.query('INSERT INTO customer (fname, sname, address) VALUES(?,?,?)',
      [customer.fname, customer.sname, customer.address ], callback);
  },

  delete: function(customer_id, callback) {
    return db.query('DELETE FROM customer WHERE customer_id=?', [customer_id], callback);
  },
  update: function(customer_id, customer, callback) {
      return db.query(
        'UPDATE customer SET fname=?, sname=?, address=? where customer_id=?',
      [customer.fname, customer.sname, customer.address, customer_id], callback);
  }

}
          
module.exports = customer;