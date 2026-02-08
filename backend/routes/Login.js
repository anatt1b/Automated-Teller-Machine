const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card');
const jwt = require('jsonwebtoken');

router.post('/', 
  function(request, response) {

    if(request.body.cardnumber && request.body.password){
      const cardnumber = request.body.cardnumber;
      const pin = request.body.password;
      
        card.checkPin(cardnumber, function(dbError, dbResult) {
          if(dbError){
            response.send("db_error");
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin,dbResult[0].pin_hash, function(err,compareResult) {
                if(compareResult) {
                  
                  console.log(dbResult[0]);
                  console.log("success");
                  const token = generateAccessToken(cardnumber);
                  response.setHeader('Content-Type', 'application/json'); 
                  const accounts = dbResult.filter(r => r.account_account_id !== null).map(r => ({
                    account_id: r.account_account_id,
                    account_type: r.account_type
                  }));
                  response.json({
                    success: true,
                    message: "Login OK",
                    token: token,
                    card_TYPE: dbResult[0].card_TYPE,
                    cardnumber: cardnumber,
                    accounts: accounts,
                    customer_id: dbResult[0].customer_customer_id
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
              console.log("card does not exists");
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