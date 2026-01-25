const express = require('express');
const router = express.Router();
const user = require('../models/customer');

// GET all customers
router.get('/',
 function(request, response) {
    user.getAll(function(err, dbResult) {
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
    user.getOne(request.params.uname, function(err, dbResult) {
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
  user.add(request.body, function(err, dbResult) {
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
  user.delete(request.params.uname, function(err, dbResult) {
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
  user.update(request.params.uname, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;