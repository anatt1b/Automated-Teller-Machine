// Import database module
const db = require('../db');

// Card_Account model contains all database operations related to the N:M relationship between cards and accounts
const cardAccount = {
  
  // Retrieves all card-account relationships from the database
  getAll: function(callback) {
    return db.query('SELECT * FROM card_account', callback);
  },

  // Retrieves a single card-account relationship by both foreign keys
  getOne: function(card_card_id, account_account_id, callback) {
    return db.query('SELECT * FROM card_account WHERE card_card_id = ? AND account_account_id = ?', [card_card_id, account_account_id], callback);
  },

  // Adds a new card-account relationship to the database
  add: function(cardAccountData, callback) {
    return db.query('INSERT INTO card_account (card_card_id, account_account_id) VALUES (?, ?)',
      [cardAccountData.card_card_id, cardAccountData.account_account_id], callback);
  },

  // Deletes a card-account relationship from the database by both foreign keys
  delete: function(card_card_id, account_account_id, callback) {
    return db.query('DELETE FROM card_account WHERE card_card_id = ? AND account_account_id = ?', [card_card_id, account_account_id], callback);
  },

  // Updates a card-account relationship by both foreign keys
  update: function(card_card_id, account_account_id, cardAccountData, callback) {
    return db.query('UPDATE card_account SET card_card_id = ?, account_account_id = ? WHERE card_card_id = ? AND account_account_id = ?',
      [cardAccountData.card_card_id, cardAccountData.account_account_id, card_card_id, account_account_id], callback);
  }

};

// Export the card_account model
module.exports = cardAccount;
