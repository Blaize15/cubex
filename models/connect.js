const mongoose = require('mongoose')
const url = "mongodb+srv://noobyco:1234@wiki-cluster.qcmha.mongodb.net/cubex?retryWrites=true&w=majority"

const connect = ()=>{

    mongoose.connect(url)
        .then((result) => { console.log("db connected!")})
        .catch((err)=>{console.log(err)})
}

module.exports = connect;