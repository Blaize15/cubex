var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const bodyParser = require("body-parser");
const connect = require('./models/connect')


// Importing Routers
var indexRouter = require('./routes/indexRouter');
var loginRouter = require('./routes/loginRouter');
var signupRouter = require('./routes/signupRouter')
const dashboardRouter = require('./routes/dashboardRoute')
const demonRouter = require("./routes/demonRoute")


var app = express();


// Connecting to mongodb
connect()


// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

//Using some juicy middleware
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
//Using body parser
app.use(bodyParser.urlencoded({extended:true}));



// Routes 
app.use('/', indexRouter);


app.use('/', loginRouter);
app.use('/', signupRouter);
app.use('/', dashboardRouter)
app.use('/', demonRouter)
// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
