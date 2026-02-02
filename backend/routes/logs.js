
const express = require('express');
const router = express.Router();
const logs = require('../models/logs');


//GET all from logs
router.get('/',
 function(request, response) {
    logs.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    })
});


//GET one log
router.get('/:logs_id',
 function(request, response) {
    logs.getOne(request.params.logs, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
});


//POST add new log 
router.post('/', 
function(request, response) {
  logs.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult); 
    }
  });
});

//DELETE log
router.delete('/:logs_id', 
function(request, response) {
  logs.delete(request.params.logs_id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

//PUT upptade logs
router.put('/:logs_id', 
function(request, response) {
  logs.update(request.params.logs_id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

