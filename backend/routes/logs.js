const express = require('express');
const router = express.Router();
const logs = require('../models/logs');


// GET logs
router.get('/:account_id', (req, res) => {
  logs.getByAccount(req.params.account_id, (err, result) => {
    if (err) return res.status(500).json(err);
    res.json(result);
  });
});



// GET /logs/latest/10
router.get('/:account_id/latest/:limit', (req, res) => {
  logs.getLatestByAccount(
    req.params.account_id,
    req.params.limit,
    (err, result) => {
      if (err) return res.status(500).json(err);
      res.json(result);
    }
  );
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



module.exports = router;