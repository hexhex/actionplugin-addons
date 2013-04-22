var casper = require("casper").create(
	{
		logLevel: "debug",
		verbose : true,
		clientScripts:  [],
		onError: function(self, m) {   // Any "error" level message will be written
			console.log('FATAL:' + m); // on the console output and PhantomJS will
			self.exit(1);               // terminate
		},
		pageSettings: {
		    loadImages:  true,        // The WebPage instance used by Casper will
		    loadPlugins: false,         // use these settings
		    javascriptEnabled: true
		},
	    stepTimeout : 600*1000
	}
);

var username;
var password;

loginURL = 'http://www.yourturnmyturn.com/';
gameURL = 'http://www.yourturnmyturn.com/reversi/play.php?gamenumber=';

if (casper.cli.has(0) && casper.cli.has(1) && casper.cli.has(2)) {
	username = casper.cli.get(0);
	password = casper.cli.get(1);
	gameURL += casper.cli.get(2);
} else {
	casper.echo("usage: casperjs makeMove.js <username> <password> <gamenumber> <row> <column>");
	casper.exit(1);
}

casper.start(loginURL, function() {
	
	console.log("START");
	
	this.fill('form[name="myform"]', { username_form: username, password_form : password }, true);
	
});

casper.thenOpen(gameURL,function() {

	var currentURL = this.getCurrentUrl();
	
	this.echo(currentURL);

	var patt=/show/;
	
	if(patt.test(currentURL)) {
		console.log("It's not my turn!");
		casper.exit(1);
	}
	
});


casper.run(function() {
	console.log("It's my turn!");
    this.exit(0);
});
