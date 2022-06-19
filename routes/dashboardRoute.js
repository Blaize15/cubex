var express = require('express');
var router = express.Router();
const dashboardController = require('../controllers/dashboardController')
const postDashboardController = require("../controllers/postDashboardController");


router.get('/dashboard', dashboardController);
router.post('/dashboard', postDashboardController);
module.exports = router;
