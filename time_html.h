#ifndef HTML_H
#define HTML_H

char* steering_html = "<!DOCTYPE html>\n<html>\n  <head>\n    <link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\">\n    <link rel=\"stylesheet\" href=\"https://code.getmdl.io/1.3.0/material.indigo-pink.min.css\">\n    <script defer src=\"https://code.getmdl.io/1.3.0/material.min.js\"></script>\n    <script\n        src=\"https://code.jquery.com/jquery-3.4.1.min.js\"\n        integrity=\"sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo=\"\n        crossorigin=\"anonymous\"></script>\n\n    <!--Let browser know website is optimized for mobile-->\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"/>\n  </head>\n  <style>\n    .pad {\n        padding: 0px 20vw\n    }\n    .tab-content {\n        height: 100%;\n        min-height: 500px;\n        max-height: 500px;\n    }\n    .button {\n        margin: 0px 20px\n    }\n    @media screen and (max-width: 1000px)  {\n        .pad {\n            padding: 0px 0vw\n        }\n\n        .tab-content {\n            height: 100%;\n            min-height: 800px;\n        }\n    }\n    @media screen and (max-width: 500px)  {\n        .button {\n            display: block;\n            margin: 10px auto;\n            min-width: 50%;\n        }\n    }\n      \n    .px-4 {\n        padding: 0px 300px\n    }\n\n    body {\n        background: #eee\n    }\n\n    .card-color {\n        background: white\n    }\n\n    .mt-3 {\n        margin-top: 20px\n    }\n\n    .invisible {\n        display: none\n    }\n\n    .green {\n        background: #00a86b !important\n    }\n\n    .red {\n        background: #da2d2d !important\n    }\n\n    .of-hidden {\n        overflow: hidden;\n    }\n\n    .mhi {\n        max-height: inherit\n    }\n\n    .row {\n        flex-direction: row;\n        display: flex;\n        justify-content: center;\n    }\n    .label {\n        padding: 10px;\n        flex: 4;\n    }\n    .textbox {\n        padding: 10px;\n        flex: 8;\n    }\n\n    .list-item {\n        border-bottom: solid lightgray 1px;\n    }\n  </style>\n  <body>\n    <div class=\"container\" style=\"text-align: center\">\n        <div style=\"padding: 10px 50px\">\n            <h2 class=\"display-3\">Nixie Tube Clock</h2>\n\n            <div class=\"mdl-grid pad\">\n                <div class=\"mdl-cell mdl-cell--12-col\">\n                    <p>Connected to <span id=\"network\" style=\"font-weight: bold; color: #00a86b\"></span></p>\n                    <button id=\"offButton\" onclick=\"switchMode(null)\" class=\"red mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect\">\n                        <i class=\"material-icons\">power_settings_new</i>\n                        Turn off\n                    </button>\n                    <button id=\"onButton\" onclick=\"switchMode(modes.clock)\" class=\"invisible mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect\">\n                        <i class=\"material-icons\">power_settings_new</i>\n                        Turn on\n                    </button>\n                </div>\n            </div>\n        </div>\n    \n        <div class=\"mt-3 pad\">\n            <div class=\"mdl-shadow--2dp tab-content of-hidden card-color\">\n\n                <div id=\"spinner\" style=\"padding: 50px\">\n                    <div class=\"mdl-spinner mdl-js-spinner is-active\"></div>\n                    <p>Connecting to clock...</p>\n                </div>\n\n                <div id=\"tabs\" class=\"invisible mdl-tabs mdl-js-tabs mdl-js-ripple-effect mhi\">\n                    <div class=\"mdl-tabs__tab-bar\">\n                        <a id=\"clock\" href=\"#clock_\" onclick=\"switchMode(modes.clock)\" class=\"clock mdl-tabs__tab clock\">Clock</a>\n                        <a id=\"stopwatch\" href=\"#stopwatch_\" onclick=\"switchMode(modes.stopwatch)\" class=\"mdl-tabs__tab stopwatch\">Stopwatch</a>\n                        <a id=\"random\" href=\"#random_\" onclick=\"switchMode(modes.random)\" class=\"mdl-tabs__tab random\">Random</a>\n                    </div>\n                    \n                    <div class=\"mdl-tabs__panel is-active clock\" style=\"font-weight: bold\" id=\"clock_\">\n                        <div class=\"row\">\n                            <div class=\"label\">\n                                <h6 style=\"font-weight: bold; text-align: right\">Timezone:</h6>\n                            </div>\n                            <div class=\"textbox\">\n                                    <div class=\"mdl-textfield mdl-js-textfield\" style=\"width:80%\">\n                                        <input id=\"timezoneName\" class=\"mdl-textfield__input\" type=\"text\" id=\"sample\">\n                                        <label id=\"timezoneNameLabel\" class=\"mdl-textfield__label\" for=\"sample\">Timezone</label>\n                                    </div>\n                            </div>\n                        </div>\n\n                        <div class=\"row\" style=\"transform: translateY(-20px)\">\n                            <div class=\"label\">\n                                <h6 style=\"font-weight: bold; text-align: right\">UTC Offset (in sec):</h6>\n                            </div>\n                            <div class=\"textbox\">\n                                    <div class=\"mdl-textfield mdl-js-textfield\" style=\"width: 80%\">\n                                        <input id=\"utcOffset\" class=\"mdl-textfield__input\" type=\"text\" pattern=\"-?[0-9]*(\.[0-9]+)?\" id=\"sample2\">\n                                        <span class=\"mdl-textfield__error\">Input is not a number!</span>\n                                        <label id=\"utcOffsetLabel\" class=\"mdl-textfield__label\" for=\"sample2\">UTC Offset</label>\n                                    </div>\n                            </div>\n                        </div>\n\n                        <div class=\"mdl-grid\" style=\"transform: translateY(-30px)\">\n                            <div class=\"mdl-cell mdl-cell--12-col\">\n                                <button onclick=\"clockController.setTimezone()\" class=\"mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect\">\n                                    <i class=\"material-icons\">check</i>\n                                    Confirm\n                                </button>\n                            </div>\n                        </div>\n\n                        <div class=\"mdl-grid\" style=\"transform: translateY(-30px)\">\n                            <div class=\"mdl-cell mdl-cell--12-col\" style=\"text-align: center; color: gray\">\n                                <h1 id=\"time\" style=\"font-size: 500%\"></h1>\n                            </div>        \n                        </div>\n                    </div>\n\n                    <div class=\"mdl-tabs__panel stopwatch mhi\" style=\"overflow: auto\" id=\"stopwatch_\">\n                        <div class=\"mdl-grid\">\n                            <div class=\"mdl-cell mdl-cell--12-col\">\n                                <button id=\"stopwatchStartButton\" onclick=\"stopwatchController.toggle()\" class=\"green button mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect\">\n                                    <div id=\"stopwatchStart\">\n                                        <i class=\"material-icons\">play_arrow</i>\n                                        Start\n                                    </div>\n                                    <div id=\"stopwatchPause\">\n                                        <i class=\"material-icons\">pause</i>\n                                        Pause\n                                    </div>\n                                </button>\n                            \n                                <button onclick=\"stopwatchController.round()\" class=\"red button mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect\">\n                                    <i class=\"material-icons\">add</i>\n                                    Round \n                                </button>\n                                <button onclick=\"stopwatchController.reset()\" class=\"mdl-button button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect\">\n                                    <i class=\"material-icons\">replay</i>\n                                    Reset\n                                </button>\n                            </div>\n                        </div>\n\n                        <div class=\"mdl-grid\">\n                            <div class=\"mdl-cell mdl-cell--12-col\">\n                                <div style=\"height: 10px\">\n                                    <div id=\"stopwatchProgress\" style=\"margin: auto\" class=\"invisible mdl-progress mdl-js-progress mdl-progress__indeterminate\"></div>\n                                </div>\n                                <h5 style=\"text-align: left; margin-left: 20px\">Times</h5>\n                                <ul id=\"rounds\" class=\"demo-list-icon mdl-list\">\n                                        \n                                </ul>\n                            </div>\n                        </div>\n                    </div>\n\n\n                    <div class=\"mdl-tabs__panel random\" id=\"random_\">\n                        <div class=\"mdl-grid\">\n                            <div class=\"mdl-cell mdl-cell--12-col\">\n                                <button id=\"stopwatchStartButton\" onclick=\"randomSeed()\" class=\"mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect\">\n                                    <div id=\"stopwatchStart\">\n                                        <i class=\"material-icons\">casino</i>\n                                        Random Seed\n                                    </div>\n                                </button>\n                            </div>\n                        </div>\n                    </div>\n                </div>\n            </div>\n        </div>\n    </div>\n  </body>\n\n  <script>\n    let baseUrl = window.location.href\n    baseUrl = baseUrl.substring(0, baseUrl.length-1)\n    let modes = {\n        clock: '.clock',\n        stopwatch: '.stopwatch',\n        random: '.random'\n    }\n    let currentMode = null;\n\n    async function switchMode(mode) {\n        currentMode = mode;\n        if (mode == modes.clock)\n            await fetch(baseUrl + '/switch/clock')\n        else if (mode == modes.stopwatch)\n            await fetch(baseUrl + '/switch/stopwatch')\n        else if (mode == modes.random)\n            await fetch(baseUrl + '/switch/random')\n        else \n            await fetch(baseUrl + '/switch/off')\n\n        setMode(currentMode);\n    }\n\n    function setMode(mode) {\n        currentMode = mode;\n        $('.mdl-tabs__tab').removeClass('is-active');\n        $('.mdl-tabs__panel').removeClass('is-active');\n        if ([modes.random, modes.stopwatch, modes.clock].includes(mode)) {\n            $('#onButton').addClass('invisible')\n            $('#offButton').removeClass('invisible')\n            $(mode).addClass('is-active');\n        } else {\n            $('#onButton').removeClass('invisible')\n            $('#offButton').addClass('invisible')\n        }\n    }\n\n    async function randomSeed() {\n        await fetch(baseUrl + '/set/random-seed')\n    }\n\n    function stringToDate(string) {\n        let numbers = string.split(':')\n        let date = new Date();\n        date.setHours(Number(numbers[0]))\n        date.setMinutes(Number(numbers[1]))\n        date.setSeconds(Number(numbers[2]))\n        return date\n    } \n\n    class ClockController {\n        async refresh() {\n            let response = await fetch(baseUrl + '/timezone')\n            response = await response.json();\n            this.timezoneName = response.name;\n            this.utcOffset = response.utcOffset;\n            $('#timezoneName').val(this.timezoneName);\n            $('#timezoneNameLabel').text('');\n            $('#utcOffset').val(this.utcOffset);\n            $('#utcOffsetLabel').text('');\n\n            response = await fetch(baseUrl + '/time')\n            response = await response.text();\n            this.time = stringToDate(response);\n\n            this.setTimeString();\n            this.interval = setInterval(() => {this.setTimeString()}, 1000);\n        }\n\n        setTimeString() {\n            this.time.setSeconds(this.time.getSeconds() + 1);\n            $('#time').text(this.time.toTimeString().substring(0, 8));\n        }\n\n        async setTimezone() {\n            clearInterval(this.interval);\n            $('#time').text('');\n            await fetch(baseUrl + '/set/timezone/name', {method: 'POST', body: $('#timezoneName').val()})\n            await fetch(baseUrl + '/set/timezone/utcOffset', {method: 'POST', body: $('#utcOffset').val()})\n            this.refresh();\n        }\n    }\n\n    class StopwatchController {\n        rounds = [];\n        running = false;\n\n        async initialize() {\n            this.renderRounds();\n            await fetch(baseUrl + '/stopwatch/stop')\n            await fetch(baseUrl + '/stopwatch/reset')\n        }\n\n        async toggle() {\n            if (!this.running) {\n                await fetch(baseUrl + '/stopwatch/start')\n                $('#stopwatchStart').addClass('invisible');\n                $('#stopwatchProgress').removeClass('invisible');\n                $('#stopwatchPause').removeClass('invisible');\n                $('#stopwatchStartButton').removeClass('green');\n                this.running = true;\n\n            } else {\n                await fetch(baseUrl + '/stopwatch/stop')\n                $('#stopwatchStart').removeClass('invisible');\n                $('#stopwatchProgress').addClass('invisible');\n                $('#stopwatchPause').addClass('invisible');\n                $('#stopwatchStartButton').addClass('green');\n                this.running = false;\n            }\n        }\n\n        async round() {\n            let response = await fetch(baseUrl + '/stopwatch/round')\n            response = await response.text();\n            let date = stringToDate(response);\n            this.rounds.push(date.toTimeString().substring(0, 8))\n            this.renderRounds()\n        }\n\n        async reset() {\n            await fetch(baseUrl + '/stopwatch/reset')\n            this.rounds = [];\n            this.renderRounds()\n        }\n\n        renderRounds() {\n            $('#rounds').empty();\n            for (let round of this.rounds) {\n                $('#rounds').append(`\n                    <li class=\"mdl-list__item list-item\" style=\"padding: 5px; max-height: 20px\">\n                        <span class=\"mdl-list__item-primary-content\">\n                        <i class=\"material-icons mdl-list__item-icon\">access_time</i>`\n                            + round +\n                        `</span>\n                    </li>`)\n            }\n        }\n    }\n\n    let clockController = new ClockController()\n    let stopwatchController = new StopwatchController()\n\n    async function initialize() {\n        let response = await fetch(baseUrl + '/mode');\n        response = await response.text();\n\n        switch (response) {\n            case 'clock':\n                setMode(modes.clock);\n                break;\n            case 'stopwatch':\n                setMode(modes.stopwatch);\n                break;\n            case 'random':\n                setMode(modes.random);\n                break;\n            default:\n                setMode(null);\n                break;\n        }\n\n        response = await fetch(baseUrl + '/network');\n        response = await response.text();\n        $('#network').text(response);\n\n        await clockController.refresh();\n        await stopwatchController.initialize();\n        $('#spinner').toggleClass('invisible');\n        $('#tabs').toggleClass('invisible');\n    }\n\n    $('document').ready(() => {\n        initialize();\n    })\n  </script>\n</html>\n      ";

#endif