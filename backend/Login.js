const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const user = require('../models/user_model');
const jwt = require('jsonwebtoken');

router.post('/', 
  function(request, response) {
    if(request.body.username && request.body.password){
      const cardnumber = request.body.username;
      const pin = request.body.password;
      
        user.checkPin(cardnumber, function(dbError, dbResult) {
          if(dbError){
            response.send("db_error");
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken(username);
                  response.setHeader('Content-Type', 'application/json'); 
                  response.json({
                    success: true,
                    message: "Login OK",
                    pin: pin,
                    token: token
                  });
                }
                else {
                    console.log("wrong pin");
                    response.json({"message":"Invalid login credentials."});
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.json({"message":"Invalid login credentials."});
            }
          }
          }
        );
      }
    else{
      console.log("cardnumber or pin missing");
      response.json({"message":"Invalid login credentials."});
    }
  }
);

function generateAccessToken(cardnumber) {
  return jwt.sign({ cardnumber }, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;