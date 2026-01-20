const express = require('express');
const router = express.Router();
const card = require('../models/card');

// GET all cards
router.get('/',
 function(request, response) {
    card.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });

//GET one card 
router.get('/:card_id',
 function(request, response) {
    card.getOne(request.params.card_id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});

// POST add new card
router.post('/', 
function(request, response) {
  card.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});


//DELETE deletes card
router.delete('/:card_id', 
function(request, response) {
  card.delete(request.params.card_id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

// PUT updates card with id. new info from request body
router.put('/:card_id', 
function(request, response) {
  card.update(request.params.card_id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;