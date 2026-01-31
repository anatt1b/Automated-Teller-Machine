const express = require('express');
const router = express.Router();
const customer = require('../models/customer');

// GET all customers
router.get('/',
 function(request, response) {
    customer.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
  });

//GET one customer by id
router.get('/:customer_id',
 function(request, response) {
    customer.getOne(request.params.customer_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

// POST add new customer
router.post('/', 
function(request, response) {
  customer.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});

//DELETE deletes customer by id
router.delete('/:customer_id', 
function(request, response) {
  customer.delete(request.params.customer_id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

// PUT updates customer with id. new info from request body
router.put('/:customer_id', 
function(request, response) {
  customer.update(request.params.customer_id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;