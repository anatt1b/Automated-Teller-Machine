const express = require('express');
const router = express.Router();
const account = require('../models/account');

//GET all accounts
router.get('/',
 function(request, response) {
    account.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
});

//GET one account 
router.get('/:account_id/:customer_customer_id',
 function(request, response) {
    account.getOne(request.params.account_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});


// POST add new account
router.post('/', 
function(request, response) {
  account.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});


//DELETE delete account
router.delete('/:account_id/:customer_customer_id', 
function(request, response) {
  account.delete(request.params.account_id,request.params.customer_customer_id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


//PUT uptades account with id
router.put('/:account_id/:customer_customer_id', 
function(request, response) {
  account.update(request.params.account_id,request.params.customer_customer_id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;