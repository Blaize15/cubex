var express = require('express');
var router = express.Router();
const loginController = require('../controllers/loginController');
const postLoginController = require('../controllers/postLoginController');

router.get('/login', loginController);

router.post('/login', postLoginController);

module.exports = router;
