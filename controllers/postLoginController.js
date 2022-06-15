const loginModel = require("../models/loginSignupModel")


const postLogin = (req, res)=>{
    const loginData = loginModel.find();
    loginData.forEach((loginCollection)=>{
        if(req.body.email == loginCollection.email && req.body.password == loginCollection.password){
            // res.render('dashboard');
            console.log("dashboard is here!")
            res.send("Dashboard");
        }
    })
};

module.exports = postLogin;