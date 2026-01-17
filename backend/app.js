const jwt = require('jsonwebtoken');
const express = require('express');
const app = express();
app.use(express.json());

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

  // Routes
const customerRoutes = require('./routes/customers');
const accountRoutes = require('./routes/accounts');
const cardRoutes = require('./routes/cards');
const cardAccountRoutes = require('./routes/card_accounts');
const accessRightsRoutes = require('./routes/access_rights');
const logsRoutes = require('./routes/logs');

app.use('/customers', customerRoutes);
app.use('/accounts', accountRoutes);
app.use('/cards', cardRoutes);
app.use('/card_accounts', cardAccountRoutes);
app.use('/access_rights', accessRightsRoutes);
app.use('/logs', logsRoutes);

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
