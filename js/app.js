(function(Box) {
    var fs  = require('fs'),
        net = require('net');

    Box = function(options) {
        this.init(options);
        this.keys = {};
    };

    Box.prototype = {
        init: function(options) {
            this.options = options;
            this._getKeys();
        },


        _getKeys: function() {
            fs.readFile('./keys.json', 'utf-8', this._handleKeysRead.bind(this));
        },


        _handleKeysRead: function(err, data) {
            if(err) {
                throw err;
            }
            this.keys = JSON.parse(data);
            this.connect();
        },


        connect: function() {
            var box = net.connect(this.options.port, this.options.host, function() {
                console.log("connecting...");
            });

            box.on('data', function(data) {
                //console.log(data.toString());
            });

            box.on('connect', function() {
                console.log('connected');
                setTimeout(this._setPrompt.bind(this, box), 1000);
            }.bind(this));
        },


        _setPrompt: function(box) {
            var readline = require('readline'),
                rl = readline.createInterface(process.stdin, process.stdout);

            rl.setPrompt('box> ');
            rl.prompt();

            rl.on('line', function(line) {
                var cmd = this._processCmd(line);
                if(cmd) {
                    box.write('key='+cmd+'\r\n');
                } else {
                    process.stdout.write("invalid cmd\r\n");
                }
                rl.prompt();
            }.bind(this));
        },


        _processCmd: function(cmd) {
            cmd = cmd.trim().toUpperCase();
            if(this.keys[cmd]) {
                return this.keys[cmd];
            }
            return false;
        }
    };
})({});
