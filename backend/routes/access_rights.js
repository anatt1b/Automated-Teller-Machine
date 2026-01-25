const express = require('express');
const router = express.Router();
const accessRights = require('../models/access_rights');

// GET all access rights
router.get('/',
 function(request, response) {
    accessRights.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });

// GET by customer
router.get('/:customer_customer_id',
 function(request, response) {
    accessRights.getByCustomer(request.params.customer_customer_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

// GET by account
router.get('/:account_account_id',
 function(request, response) {
    accessRights.getByAccount(request.params.account_account_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

// GET by both customer and account
router.get('/:customer_customer_id/:account_account_id',
 function(request, response) {
    accessRights.getOne(request.params.customer_customer_id,request.params.account_account_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

// POST add new access right
router.post('/', 
function(request, response) {
  accessRights.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});

//DELETE deletes customer by both customer and account ids
router.delete('/:customer_customer_id/:account_account_id', 
function(request, response) {
  accessRights.delete(request.params.customer_customer_id, request.params.account_account_id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

// PUT updates access right by both customer and account ids
router.put('/:customer_customer_id/:account_account_id', 
function(request, response) {
  accessRights.update(request.params.customer_customer_id, request.params.account_account_id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
