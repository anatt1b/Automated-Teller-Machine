// Import database module
const db = require('../db');
// Import bcrypt library for hashing PIN codes
const bcrypt = require('bcryptjs');

// Defines the number of salt rounds for hashing difficulty
const saltRounds = 10;

// Card model contains all database operations related to cards
const card = {
  
  // Retrieves all cards from the database
  getAll: function(callback) {
    return db.query('SELECT * FROM card', callback);
  },

  // Retrieves a single card by ID
  getOne: function(card_id, callback) {
    return db.query('SELECT * FROM card WHERE card_id = ?', [card_id], callback);
  },

  // Retrieves the hashed PIN (pin_hash) for a card using the card number.
  // Used during login to verify the entered PIN with bcrypt.compare().
  // Does NOT return the plaintext PIN, only the stored hash.
  checkPin: function(cardnumber, callback){
    return db.query('SELECT pin_hash FROM card WHERE cardnumber = ?', [cardnumber], callback);
  },

  // Adds a new card to the database and hashes the PIN code
  add: function(cardData, callback) {
    bcrypt.hash(cardData.pin_hash, saltRounds, function(err, hash) {
      if (err) return callback(err);
      return db.query('INSERT INTO card (cardnumber, pin_hash, card_TYPE, customer_customer_id) VALUES (?, ?, ?, ?)',
        [cardData.cardnumber, hash, cardData.card_TYPE, cardData.customer_customer_id], callback);
    });
  },

  // Deletes a card from the database by ID
  delete: function(card_id, callback) {
    return db.query('DELETE FROM card WHERE card_id = ?', [card_id], callback);
  },

  // Updates card information and hashes the new PIN code
  update: function(card_id, cardData, callback) {
    bcrypt.hash(cardData.pin_hash, saltRounds, function(err, hash) {
      if (err) return callback(err);
      return db.query('UPDATE card SET cardnumber = ?, pin_hash = ?, card_TYPE = ?, customer_customer_id = ? WHERE card_id = ?',
        [cardData.cardnumber, hash, cardData.card_TYPE, cardData.customer_customer_id, card_id], callback);
    });
  }

};

// Export the card model
module.exports = card;
