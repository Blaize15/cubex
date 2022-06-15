const loginModel = require("../models/loginSignupModel")


const postSignupCOntroller = (req, res)=>{
    const name = req.body.name;
    console.log(name)

    const signup = new loginModel({
        name : req.body.name,
        email : req.body.email,
        password : req.body.password,
    });

    signup.save()
        .then((results)=>{
            res.redirect('/login')
        })
        .catch((err)=>{
            console.log(err);
        })

    
};

module.exports = postSignupCOntroller;