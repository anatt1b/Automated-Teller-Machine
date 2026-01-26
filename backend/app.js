const jwt = require('jsonwebtoken');
const express = require('express');
const app = express();
app.use(express.json());

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401);
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403);
  
      req.user = user
  
      next();
    });
  }

  // Routes
const customerRoutes = require('./routes/customer');
const accountRoutes = require('./routes/account');
const cardRoutes = require('./routes/card');
const cardAccountRoutes = require('./routes/card_account');
const accessRightsRoutes = require('./routes/access_rights');
const logsRoutes = require('./routes/logs');

app.use('/customer', customerRoutes);
app.use('/account', accountRoutes);
app.use('/card', cardRoutes);
app.use('/card_account', cardAccountRoutes);
app.use('/access_right', accessRightsRoutes);
app.use('/logs', logsRoutes);

app.get('/health', (req, res) => res.json({ ok: true}));

module.exports = app;
