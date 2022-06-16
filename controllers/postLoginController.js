const loginModel = require("../models/loginSignupModel")


const postLogin = (req, res)=>{

    loginModel.find({ email: req.body.email}, function (err, docs) {
        if (err){
            console.log(err);
        }
        else if(docs[0].password == req.body.password){
            res.redirect('/dashboard');
        }else{
            console.log("Password or email incorrect")
        }
    });

};

module.exports = postLogin;