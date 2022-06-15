var express = require('express');
var router = express.Router();
const signupController = require('../controllers/signupController')
const postSignupController = require('../controllers/postSignupController')


router.get('/signup', signupController);


router.post('/signup', postSignupController);

module.exports = router;
