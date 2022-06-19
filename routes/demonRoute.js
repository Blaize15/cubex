var express = require('express');
var router = express.Router();

const demonController = require("../controllers/demonController");
router.get("/dashboard/demon", demonController);

module.exports = router;