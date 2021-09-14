var express = require('express');
var app = express();
var handlebars = require('express3-handlebars').create({defaultLayout: 'main'});
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', process.env.PORT || 8080);


app.get('/', function(req, res) {
	res.render('home');
});



app.use((req, res) => {
	res.status(404);
	res.render('404');
});

app.use((err, req, res, next) => {
	console.log(err.stack);
	res.status(500);
	res.render('500');
});

app.listen(app.get('port'), () => {
	console.log('listening on port ' + app.get('port'));
});