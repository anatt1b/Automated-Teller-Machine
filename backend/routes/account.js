const express = require('express');
const router = express.Router();
const account = require('../models/account');
const logs = require('../models/logs');

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
    account.getOne(request.params.account_id, request.params.customer_customer_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        // available_credit = credit_limit -used_credit
          if(dbResult.length > 0){
            const row = dbResult[0];

            const creditLimit = Number(row.credit_limit || 0);
            const usedCredit = Number(row.used_credit || 0);

            row.available_credit = creditLimit -usedCredit;

            //daily withdraw limit
            const dailyLimit = Number(row.daily_withdraw_limit || 0);
            row.daily_withdraw_limit = dailyLimit;
          }
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