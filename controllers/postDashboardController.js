
const mqtt = require('mqtt')
const client  = mqtt.connect('mqtt://broker.emqx.io')


const postDashboardController = (req, res)=>{
    const cubex1 = req.body.cubex1;
    const cubex2 = req.body.cubex2;
    const demonName = req.body.name;
    client.publish("cubex/cubex" + cubex1 && "cubex/cubex" + cubex2 , "enable demon")
   
    res.render('demon')
    
}    


module.exports = postDashboardController;