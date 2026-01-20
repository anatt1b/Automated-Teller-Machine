const express = require('express');
const router = express.Router();
const cardAccount = require('../models/card_account');

// GET all card accounts
router.get('/',
 function(request, response) {
    cardAccount.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });

//GET one card account 
router.get('/:card_card_id/:account_account_id',
 function(request, response) {
    cardAccount.getOne(request.params.card_card_id, request.params.account_account_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

// POST add new card account
router.post('/', 
function(request, response) {
  cardAccount.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});


//DELETE deletes card account
router.delete('/:card_card_id/:account_account_id', 
function(request, response) {
  cardAccount.delete(request.params.card_card_id, request.params.account_account_id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

// PUT updates card account with id. new info from request body
router.put('/:card_card_id/:account_account_id', 
function(request, response) {
  cardAccount.update(request.params.card_card_id, request.params.account_account_id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
