const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const blogObj = {
    name : {type : String, required : true},
    email : {type : String, required : true},
    password : {type : String, required : true}
}
const blogSchema = new Schema(blogObj, {timestamps : true});

const loginSignup = mongoose.model('login', blogSchema);

module.exports = loginSignup;