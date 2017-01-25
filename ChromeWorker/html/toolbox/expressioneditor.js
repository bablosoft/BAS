        function ExpressionEditor(ResultCallback, OldValue, OriginalData)
        {
            var t = new Date()

            var Result = ""
            var ValueSelectorCallback = null
            var Loader = new ResourceLoader()
            var LoadLinks = []
            Loader.SetIsPrerender(true)

            function PrepareData()
            {
                var json = graph.toJSON()["cells"]
                var res = []
                var ids = {}
                var currentid = 0
                for(var i = 0;i<json.length;i++)
                {
                    var el = json[i]
                    
                    if(el.hasOwnProperty("type") && el["type"] == "link")
                    {

                        {
                            var id = el["target"]["id"]
                            if(!ids.hasOwnProperty(id))
                            {
                                ids[id] = currentid.toString()
                                currentid ++;
                            }
                            el["target"]["id"] = ids[id]
                        }
                        {
                            var id = el["source"]["id"]
                            if(!ids.hasOwnProperty(id))
                            {
                                ids[id] = currentid.toString()
                                currentid ++;
                            }
                            el["source"]["id"] = ids[id]
                        }
                        
                        delete el["target"]["selector"];
                        delete el["source"]["selector"];
                        delete el["connector"];
                        delete el["id"];
                        delete el["embeds"];
                        delete el["z"];
                        delete el["attrs"];
                        if(el.hasOwnProperty("vertices"))
                            delete el["vertices"];
                    }else
                    {
                        {
                            var id = el["id"]
                            if(!ids.hasOwnProperty(id))
                            {
                                ids[id] = currentid.toString()
                                currentid ++;
                            }
                            el["id"] = ids[id]
                        }
                        delete el["attrs"];
                        delete el["z"];
                        delete el["angle"];
                        delete el["size"];
                        delete el["type"];
                        delete el["inPorts"];
                        delete el["outPorts"];
                        var x = el["position"]["x"]
                        var y = el["position"]["y"]
                        delete el["position"]
                        el["x"] = x
                        el["y"] = y


                        if(el.hasOwnProperty("name") && el["name"] == "value")
                        {
                            
                        }else if(el.hasOwnProperty("name") && el["name"] == "result")
                        {
                            delete el["data"];
                        }else if(el.hasOwnProperty("name") && el["name"] == "custom")
                        {
                            
                        }else
                        {
                            delete el["data"];
                        }
                    }

                    res.push(el)
                }
                return JSON.stringify(res)
            }

            function RestoreData()
            {
                var json = JSON.parse(OriginalData)
                var res = []
                LoadLinks = []
                for(var i = 0;i<json.length;i++)
                {
                    var el = json[i]
                    if(el.hasOwnProperty("type") && el["type"] == "link")
                    {
                        LoadLinks.push({
                         source: {
                           id: el["source"]["id"],
                           port: el["source"]["port"]

                         },
                         target: {
                           id: el["target"]["id"],
                           port: el["target"]["port"]
                         },
                         attrs: { '.marker-target': { d: 'M 10 0 L 0 5 L 10 10 z' } },
                         connector: { name: 'smooth' }
                        });
                        
                        
                    }else
                    {

                        if(el.hasOwnProperty("name") && el["name"] == "value")
                        {
                            var value = el["data"]
                            if(value.length > 16)
                                value = value.slice(0,13) + "..."

                            el["size"] = {"width":100,"height":40}
                            el["type"] = "devs.EditAndDelete"

                            el["inPorts"] = []
                            el["outPorts"] = ["-"]

                            el["attrs"] = {
                                '.label': { text: tr("Value") + ":\n" + value, "y":"0.7em" },
                                rect: { fill: '#F0F0F0' },
                                '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                            }
                        }else if(el.hasOwnProperty("name") && el["name"] == "result")
                        {
                            el["size"] = {"width":70,"height":70}
                            el["type"] = "devs.Model"

                            el["inPorts"] = ["-"]
                            el["outPorts"] = []
                            el["data"] = "<<0>>"

                            el["attrs"] = {
                                '.label': { text: tr("result"), "y":"2.5em", fill: "black" },
                                rect: { fill: '#F0F0F0', "stroke-width":"1", "rx":"2000", "ry":"2000" },
                                '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                            }
                        }else if(el.hasOwnProperty("name") && el["name"] == "custom")
                        {
                            el["size"] = {"width":100,"height":40}
                            el["type"] = "devs.Delete"

                            var value = el["data"]

                            el["inPorts"] = _.map(_.uniq(value.match(new RegExp("\\<\\<\\d+\\>\\>","g"))),function(x,i){return "arg" + i;})
                            el["outPorts"] = ["-"]

                            if(value.length > 16)
                                value = value.slice(0,13) + "..."
                            el["attrs"] = {
                                    '.label': { text: tr("Code") + ":\n" + value, "y":"0.7em" },
                                    rect: { fill: '#F0F0F0' },
                                    '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                    '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                    '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                                }
                        }else
                        {
                            el["size"] = {"width":100,"height":40}
                            var value = el["name"]
                            
                            var action = FindAction(value)
                            el["inPorts"] = _.map(action["params"], function(e){ return e["name"] })
                            el["outPorts"] = ["-"]
                            el["data"] = action["code"]

                            value = tr(value)

                            if(value.length > 16)
                                value = value.slice(0,13) + "..."



                            el["type"] = "devs.Delete"

                            el["attrs"] = {
                                '.label': { text: value, "y":"1.2em" },
                                rect: { fill: '#F0F0F0' },
                                '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                            }
                        }

                        el["position"] = {x:el["x"],y:el["y"]}
                        delete el["x"]
                        delete el["y"]
                            
                        res.push(el)
                    }
                }
                UpdatePorts();



                graph.fromJSON({"cells":res})
               
                
            }

            //console.log("Load time1 " + (new Date() - t) )



            $("#expressioneditor-container").html(_.template($('#expressioneditor').html())({}))

            $("#expressioneditor-valuecancel").click(function(){
                $("#expressioneditor-overlay").hide()
                return false
            })


            $("#expressioneditor-valueok").click(function(){
                $("#expressioneditor-overlay").hide()
                if(ValueSelectorCallback)
                {
                    ValueSelectorCallback()
                    ValueSelectorCallback = null
                }
                
                return false
            })

            //console.log("Load time2 " + (new Date() - t) )

            $("#expressioneditor-cancel").click(function(){

                ResultCallback({ok:false})
                return false
            })

            $("#expressioneditor-ok").click(function(){
                if(OldValue != "\"\"")
                {
                    var OldValuePart = OldValue
                    if(OldValuePart.length > 500)
                    {
                        OldValuePart = OldValuePart.slice(0,497) + "..."
                    }
                    $("#expressioneditor-old-value").html(OldValuePart)
                    $("#ExpressionValueConfirm").html(Result)
                    $("#expressioneditor-overlay-confirm").show()
                    $("#ExpressionValueConfirm").closest(".input-group").find(".input_selector_number").hide()
                    $("#ExpressionValueConfirm").closest(".input-group").find(".input_selector_string").show()
                    $("#ExpressionValueConfirm").closest(".input-group").find(".selector").html("expression")
                    $("#ExpressionValueConfirm").val(Result)
                }else
                {
                    ResultCallback({ok:true, res:Result, data:PrepareData()})
                }
                return false
            })

            $("#expressioneditor-confirmok").click(function(){
                var V = GetInputConstructorValue("ExpressionValueConfirm",Loader)
                Result = V["updated"]
                ResultCallback({ok:true, res:Result, data:PrepareData()})
                return false
            })  

            $("#expressioneditor-confirmcancel").click(function(){
                ResultCallback({ok:false})
                return false
            })

            //console.log("Load time3 " + (new Date() - t) )            

            joint.shapes.devs.Delete = joint.shapes.devs.Model.extend(_.extend({}, joint.plugins.TooledModelInterface, {

            markup: ['<g class="rotatable">',
                        '<g class="scalable">',
                            '<rect class="body"/>',
                        '</g>',
                        '<text class="label"/>',
                        '<g class="inPorts"/>',
                        '<g class="outPorts"/>',
                        '<g class="deleteTool" transform="translate(100, 0) scale(0.6)" style="cursor: hand" />',
                        '<title class="tooltip"/>',
                    '</g>'].join(''),

            defaults: joint.util.deepSupplement({
                type: 'devs.Delete'

            }, joint.shapes.devs.Model.prototype.defaults),
            }));
            joint.shapes.devs.DeleteView = joint.shapes.devs.ModelView.extend(joint.plugins.TooledViewInterface);


            joint.shapes.devs.EditAndDelete = joint.shapes.devs.Model.extend(_.extend({}, joint.plugins.TooledModelInterface, {

            markup: ['<g class="rotatable">',
                        '<g class="scalable">',
                            '<rect class="body"/>',
                        '</g>',
                        '<text class="label"/>',
                        '<g class="inPorts"/>',
                        '<g class="outPorts"/>',
                        '<g class="deleteTool" transform="translate(100, 0) scale(0.6)" style="cursor: hand" />',
                        '<g class="editAndDeleteTool" transform="translate(80, 0) scale(0.6)" style="cursor: hand" />',
                        '<title class="tooltip"/>',
                    '</g>'].join(''),

            defaults: joint.util.deepSupplement({
                type: 'devs.EditAndDelete'

            }, joint.shapes.devs.Model.prototype.defaults),
            }));
            joint.shapes.devs.EditAndDeleteView = joint.shapes.devs.ModelView.extend(joint.plugins.TooledViewInterface);

            //console.log("Load time4 " + (new Date() - t) )            

            var graph = new joint.dia.Graph;
            var paper = new joint.dia.Paper({
                width: 4000, height: 4000, gridSize: 1,
                model: graph,
                defaultLink: new joint.dia.Link({
                    attrs: { '.marker-target': { d: 'M 10 0 L 0 5 L 10 10 z' } },
                    connector: { name: 'smooth' }
                }),
                validateConnection: function(cellViewS, magnetS, cellViewT, magnetT, end, linkView) {
                    
                    if (magnetS && magnetS.getAttribute('type') === 'input') return false;
                    
                    var links = graph.getLinks()
                    for(var i = 0;i<links.length;i++)
                    {
                        var link = links[i]
                        if(link.id != linkView.model.get("id"))
                        {
                            if(link.get("target").id == cellViewT.model.id && link.get("target").port == magnetT.getAttribute('port'))
                            {
                                return false
                            }
                        }
                    }

                    
                    if (cellViewS === cellViewT) return false;
                    
                    return magnetT && magnetT.getAttribute('type') === 'input';
                },
                linkPinning: false,
                snapLinks: { radius: 75 },
                markAvailable: true,
                multiLinks: false
            });

            var paperScroller = new joint.ui.PaperScroller({
                paper: paper
            });

            //console.log("Load time5 " + (new Date() - t) )            

            $('#expressioneditor-constructor').append(paperScroller.render().el);

            this.UpdatePosition = function()
            {

                paperScroller.$el.css({
                    width: $(".expressioneditor-container").width() + 30,
                    height: document.documentElement.clientHeight - 5
                });

                $("#expressioneditor-expression").css("top",(document.documentElement.clientHeight - 42).toString() + "px")

                $("#expressioneditor-list").height(document.documentElement.clientHeight - 5)
                $(".expressioneditor-bottom-titlebar").css("top",(document.documentElement.clientHeight - 45).toString() + "px")

            }

            paper.on('blank:pointerdown', paperScroller.startPanning);

            //console.log("Load time6 " + (new Date() - t) )            


            paperScroller.$el.css("overflow","hidden")

            this.UpdatePosition();

            var nav = new joint.ui.Navigator({
                paperScroller: paperScroller,
                width: 170,
                height: 170,
                padding: 0,
                zoomOptions: { max: 2, min: 0.2 }
            });
            nav.$el.appendTo('.expressioneditor-navigator');
            nav.render();

            paperScroller.zoom(-0.1);
            $('.paper-scroller').on('mousewheel', function(event) {

                if(event.deltaY > 0)
                    paperScroller.zoom(0.05, { max: 2});
                else
                    paperScroller.zoom(-0.05, { min: 0.4});

                return false
            });

            //console.log("Load time7 " + (new Date() - t) )            


    		var actions = [
                /* Logical */
                {name: "==", description: "Returns true if value1 equal value2, otherwise false", code: "(<<0>>) == (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: "<", description: "Returns true if value1 is less than value2, otherwise false", code: "(<<0>>) < (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: "<=", description: "Returns true if value1 is not greater than value2, otherwise false", code: "(<<0>>) <= (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: ">", description: "Returns true if value1 is greater than value2, otherwise false", code: "(<<0>>) > (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: ">=", description: "Returns true if value1 is not less than value2, otherwise false", code: "(<<0>>) >= (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: "and", description: "Returns true if value1 is true and value2 is true, otherwise false", code: "(<<0>>) && (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: "or", description: "Returns true if value1 is true or value2 is true, otherwise false", code: "(<<0>>) || (<<1>>)", params: [{name: "value1"},{name: "value2"}]},
                {name: "not", description: "Returns true if value is false and false if value is true", code: "!(<<0>>)", params: [{name: "value"}]},
                {name: "if", description: "Returns value1 if expression true and value2 otherwise", code: "(<<0>>) ? (<<1>>) : (<<2>>)", params: [{name: "expression"},{name: "value1"},{name: "value2"}]},
                
                /* String */
                {name: "concat", description: "Add one string to another", code: "(<<0>>) + (<<1>>)", params: [{name: "first"},{name: "second"}]},
                {name: "length", description: "Returns string length", code: "(<<0>>).length", params: [{name: "string"}]},
                {name: "contains", description: "Check if one string contains another", code: "(<<0>>).indexOf(<<1>>) >= 0", params: [{name: "string"},{name: "value"}]},
                {name: "substring", description: "Takes substring from a given string. First param - string, second - first index, third - second index", code: "(<<0>>).substring(<<1>>,<<2>>)", params: [{name: "string"},{name: "index1"},{name: "index2"}]},
                {name: "search", description: "Searches for string part inside string, if found returns found index, otherwise returns -1", code: "(<<0>>).indexOf(<<1>>)", params: [{name: "string"},{name: "string part"}]},
                {name: "replace", description: "Replace all occurrences of one string with another", code: "(<<0>>).split(<<1>>).join(<<2>>)", params: [{name: "string"},{name: "replace from"},{name: "replace to"}]},
    			{name: "split with string", description: "Splits string with defined separator. Returns array of strings", code: "(<<0>>).split(<<1>>)", params: [{name: "array"},{name: "separator"}]},
                {name: "split with regexp", description: "Splits string with defined regexp. Returns array of strings", code: "(<<0>>).split(/<<1>>/)", params: [{name: "string"},{name: "regexp"}]},
                {name: "matches", description: "Returns true if string matches given regexp", code: "Boolean((<<0>>).match(/<<1>>/))", params: [{name: "string"},{name: "regexp"}]},
                {name: "scan", description: "Extract string part with regular expression. For example, string : abc 123 xyz 456, regexp: \\d+ extracts all numbers", code: "(function(){var rs = []; var r = /<<1>>/gm; var s = <<0>>; var m; var i = -1; while(m = r.exec(s)){if(i == m.index) break; i = m.index; rs.push((m.length>1) ? m[1] : m[0]);} return rs;})()", params: [{name: "string"},{name: "regexp"}]},

                /* Random */
                {name: "random number", description: "Generate random number", code: "Math.floor(Math.random() * (<<0>> - <<1>> + 1)) + <<1>>", params: [{name: "max"},{name: "min"}]},
                {name: "random string", description: "Generate random string", code: "Array(<<0>>).join().split(',').map(function() { return \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\".charAt(Math.floor(Math.random() * 62)); }).join('')", params: [{name: "length"}]},
                {name: "random alphabet", description: "Generate random string, with given alphabet. Alphabet is just a string, for example, if alphabet is 01 action will generate random binary number", code: "Array(<<1>>).join().split(',').map(function() { return (<<0>>).charAt(Math.floor(Math.random() * <<0>>.length)); }).join('')", params: [{name: "alphabet"},{name: "length"}]},

                
                /* Array */
                {name: "empty array", description: "Creates empty array", code: "[]", params: []},
                {name: "create array", description: "Creates array with single element", code: "[ <<0>> ]", params: [{name: "element"}]},
                {name: "array push", description: "Add value to the end of array", code: "(<<0>>).concat([ <<1>> ])", params: [{name: "array"}, {name: "value"}]},
                {name: "array concat", description: "Concat several arrays", code: "(<<0>>).concat(<<1>>)", params: [{name: "array1"}, {name: "array2"}]},
                {name: "array insert", description: "Add value to specific place of array", code: "(<<0>>).slice(0,<<2>>).concat([ <<1>> ].concat((<<0>>).slice(<<2>>,(<<0>>).length)))", params: [{name: "array"}, {name: "value"}, {name: "index"}]},
                {name: "array length", description: "Get array length", code: "(<<0>>).length", params: [{name: "array"}]},
                {name: "array get index", description: "Get element from array by index", code: "(<<0>>)[ <<1>> ] || null", params: [{name: "array"}, {name: "index"}]},
    			{name: "array join", description: "Join array of strings with defined separator", code: "(<<0>>).join(<<1>>)", params: [{name: "array"},{name: "separator"}]},
                {name: "subarray", description: "Takes subarray from a given array. First param - array, second - first index, third - second index", code: "(<<0>>).slice(<<1>>,<<2>>)", params: [{name: "array"},{name: "index1"},{name: "index2"}]},


                /* Numbers */
                {name: "+", description: "Adds numbers", code: "(<<0>>) + (<<1>>)", params: [{name: "number1"},{name: "number2"}]},
                {name: "-", description: "Substracts numbers", code: "(<<0>>) - (<<1>>)", params: [{name: "number1"},{name: "number2"}]},
                {name: "*", description: "Multiply numbers", code: "(<<0>>) * (<<1>>)", params: [{name: "number1"},{name: "number2"}]},
                {name: "/", description: "Divide numbers", code: "(<<0>>) / (<<1>>)", params: [{name: "number1"},{name: "number2"}]},

                /* Custom code */
                {name: "custom", description: "Execute custom code", code: "", params: []}
                
                
    		]

            //console.log("Load time8 " + (new Date() - t) )            

    		/* Populate all actions */
            {
              var text = ""
              var templ = $('#expressioneditor-list-item').html()
              for(var i = 0;i<actions.length;i++)
              {
                var action = actions[i]
                text += _.template(templ)({name:action["name"], name_translate:tr(action["name"]), description:tr(action["description"])})
              }

              $("#expressioneditor-list").html(text)
            }

            //console.log("Load time9 " + (new Date() - t) )            

            

            function FindAction(name)
            {
                for(var i = 0;i<actions.length;i++)
                {
                    var action = actions[i]
                    if(action["name"] == name)
                    {
                        return action
                    }
                }
                return null
            }

            function EditValue(model)
            {
                $("#expressioneditor-overlay").show();
                var datatype = model.get("datatype");
                $("#ExpressionValue").val("")
                $("#ExpressionValue_number").val("1")

                if(datatype == "string" || datatype == "expression")
                {
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_number").hide()
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_string").show()
                    $("#ExpressionValue").val(model.get("dataoriginal"))    
                }else
                {
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_number").show()
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_string").hide()
                    $("#ExpressionValue_number").val(model.get("dataoriginal"))    
                }
                
                $("#ExpressionValue").closest(".input-group").find(".selector").html(datatype)

                ValueSelectorCallback = function()
                {
                    var V = GetInputConstructorValue("ExpressionValue",Loader)
                    var value = V["updated"]

                    if(value && value.length > 0)
                    {
                        value = value.replace("\n"," ")
                        var data = value
                        if(value.length > 16)
                            value = value.slice(0,13) + "..."
                        model.set("data",data)
                        model.set("dataoriginal",V["original"])
                        model.set("datatype",$("#ExpressionValue").closest(".input-group").find(".selector").html())


                        model.attr('.label/text', tr("Value") + ":\n" + value);
                        UpdatePorts()
                    }
                }
            }

            //console.log("Load time8 " + (new Date() - t) )            

            if(OriginalData.length == 0)
            {
                var res = new joint.shapes.devs.Model({
                    position: { x: 2200, y: 2000},
                    size: { width: 70, height: 70 },
                    inPorts: ['-'],
                    outPorts: [],
                    attrs: {
                        '.label': { text: tr("result"), "y":"2.5em", fill: "black" },
                        rect: { fill: '#F0F0F0', "stroke-width":"1", "rx":"2000", "ry":"2000" },
                        '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                        '.inPorts text': { y:'0.4em', "font-style": "italic" },
                        '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                    },
                    name: "result",
                    data: "<<0>>"
                });
                graph.addCell(res);

                var cell = new joint.shapes.devs.EditAndDelete({
                            
                            position: { x: 2000, y: 1950},
                            size: { width: 100, height: 40 },
                            inPorts: [],
                            outPorts: ['-'],
                            attrs: {
                                '.label': { text: tr("Value") + ":\n\"test\"", "y":"0.7em" },
                                rect: { fill: '#F0F0F0' },
                                '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                            },
                            name: "value",
                            data: "\"test\"",
                            dataoriginal: "test",
                            datatype: "string",
                            edit: EditValue
                        });
                        graph.addCell(cell);

                var link = new joint.dia.Link({
                     source: {
                       id: cell.id,
                       port: '-'
                     },
                     target: {
                       id: res.id,
                       port: '-'
                       
                     },
                     attrs: { '.marker-target': { d: 'M 10 0 L 0 5 L 10 10 z' } },
                     connector: { name: 'smooth' }
                   });
                  graph.addCell(link)
            }else
            {
                RestoreData()
                //console.log("Load time9 " + (new Date() - t) )            
                var cells = graph.getCells()
                for(var i = 0;i<cells.length;i++)
                {
                    cells[i].set("edit",EditValue)
                }
                //console.log("Load time10 " + (new Date() - t) )            

                UpdatePorts()
                //console.log("Load time11 " + (new Date() - t) )            
            }



            paperScroller.centerContent();

            //console.log("Load time12 " + (new Date() - t) )            

            $(".expressioneditor-tool").click(function(e){
                var name = $(e.currentTarget).attr("data-name")
                var action = FindAction(name)
                if(action == null)
                    return false


                if(name == "custom")
                {
                    $("#expressioneditor-overlay").show();

                    $("#ExpressionValue").val("")
                    $("#ExpressionValue_number").val("1")

                    $("#ExpressionValue").closest(".input-group").find(".input_selector_number").hide()
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_string").show()
                    $("#ExpressionValue").closest(".input-group").find(".selector").html("expression")


                    ValueSelectorCallback = function()
                    {
                        var V = GetInputConstructorValue("ExpressionValue",Loader)
                        var value = V["updated"]


                        if(value && value.length > 0)
                        {
                            value = value.replace("\n"," ")
                            var data = value
                            if(value.length > 16)
                                value = value.slice(0,13) + "..."
                            var cell = new joint.shapes.devs.Delete({
                                position: { x: (1.0 / paperScroller._sx) *paperScroller.$el[0].scrollLeft + 100 + Math.floor(Math.random() * 50) - 50, y: (1.0 / paperScroller._sy) *paperScroller.$el[0].scrollTop + 100  + Math.floor(Math.random() * 50) - 50},
                                size: { width: 100, height: 40 },
                                inPorts: _.map(_.uniq(data.match(new RegExp("\\<\\<\\d+\\>\\>","g"))),function(x,i){return "arg" + i;}),
                                outPorts: ['-'],
                                attrs: {
                                    '.label': { text: tr("Code") + ":\n" + value, "y":"0.7em" },
                                    rect: { fill: '#F0F0F0' },
                                    '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                    '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                    '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                                },
                                name: "custom",
                                data: data
                            });
                            graph.addCell(cell);
                        }
                    }
                }else
                {
                    var name_tr = tr(action["name"])
                    if(name_tr.length > 16)
                        name_tr = name_tr.slice(0,13) + "..."
                    var cell = new joint.shapes.devs.Delete({
                        position: { x: (1.0 / paperScroller._sx) *paperScroller.$el[0].scrollLeft + 100 + Math.floor(Math.random() * 50) - 50, y: (1.0 / paperScroller._sy) *paperScroller.$el[0].scrollTop + 100  + Math.floor(Math.random() * 50) - 50},
                        size: { width: 100, height: 40 },
                        inPorts: _.map(action["params"], function(e){ return e["name"] }),
                        outPorts: ['-'],
                        attrs: {
                            '.label': { text: name_tr, "y":"1.2em" },
                            rect: { fill: '#F0F0F0' },
                            '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                            '.inPorts text': { y:'0.4em', "font-style": "italic" },
                            '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                        },
                        name: action["name"],
                        data: action["code"]
                    });
                    graph.addCell(cell);
                }

                return false;

            })

            //console.log("Load time13 " + (new Date() - t) )            


            


            
           

            
            $(".expressioneditor-add-string, .expressioneditor-add-int, .expressioneditor-add-expression").click(function(e){
                
                $("#expressioneditor-overlay").show();

                $("#ExpressionValue").val("")
                $("#ExpressionValue_number").val("1")


                
                if($(e.toElement).closest(".btn").hasClass("expressioneditor-add-int"))
                {
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_number").show()
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_string").hide()
                    $("#ExpressionValue").closest(".input-group").find(".selector").html("int") 
                }else if($(e.toElement).closest(".btn").hasClass("expressioneditor-add-expression"))
                {
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_number").hide()
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_string").show()
                    $("#ExpressionValue").closest(".input-group").find(".selector").html("expression") 
                }else
                {
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_number").hide()
                    $("#ExpressionValue").closest(".input-group").find(".input_selector_string").show()
                    $("#ExpressionValue").closest(".input-group").find(".selector").html("string")    
                }

                




                 ValueSelectorCallback = function()
                {
                    var V = GetInputConstructorValue("ExpressionValue",Loader)
                    var value = V["updated"]

                    if(value && value.length > 0)
                    {
                        value = value.replace("\n"," ")
                        var data = value
                        if(value.length > 16)
                            value = value.slice(0,13) + "..."
                        var cell = new joint.shapes.devs.EditAndDelete({
                            position: { x: (1.0 / paperScroller._sx) *paperScroller.$el[0].scrollLeft + 100 + Math.floor(Math.random() * 50) - 50, y: (1.0 / paperScroller._sy) *paperScroller.$el[0].scrollTop + 100  + Math.floor(Math.random() * 50) - 50},
                            size: { width: 100, height: 40 },
                            inPorts: [],
                            outPorts: ['-'],
                            attrs: {
                                '.label': { text: tr("Value") + ":\n" + value, "y":"0.7em" },
                                rect: { fill: '#F0F0F0' },
                                '.inPorts circle': { fill: '#16A085', magnet: 'passive', type: 'input', r: 7 },
                                '.inPorts text': { y:'0.4em', "font-style": "italic" },
                                '.outPorts circle': { fill: '#E74C3C', type: 'output', r: 7 }
                            },
                            name: "value",
                            data: data,
                            edit: EditValue,
                            dataoriginal: V["original"],
                            datatype: $("#ExpressionValue").closest(".input-group").find(".selector").html()
                        });
                        graph.addCell(cell);
                    }
                }


                return false;

            })

            //console.log("Load time14 " + (new Date() - t) )            



            function UpdatePorts()
            {
                var texts = $(".port text tspan")
                for(var i = 0;i<texts.length;i++)
                {
                    var t = $(texts[i])
                    t.html(tr(t.text()))
                }

                $(".outPorts .port text").hide();
                var inports = $(".inPorts .port")
                for(var i = 0;i<inports.length;i++)
                {
                    var el = $(inports[i])
                    if(el.find("tspan").text()!="-")
                    {
                        el.find("circle").attr("transform","translate(-" + (el.find("text")[0].getBBox().width + 15) +  ",0)")
                        el.find("tspan").attr("x","-5")
                    }else
                    {
                        el.find("text").hide()
                    }
                    
                }
                
            }

            UpdatePorts();

            //console.log("Load time15 " + (new Date() - t) )            

            function UpdateResult()
            {

                var temp_data = {}
                Result = ""
                $("#expressioneditor-expression").html("")
                var elements = graph.getElements()
                for(var i=0;i<elements.length;i++)
                {
                    var element = elements[i]
                    temp_data[element.get("id")] = null
                }

                while(true)
                {
                    var number_of_changes = 0
                    var result_saved = false
                    for(var j=0;j<elements.length;j++)
                    {
                        var element = elements[j]
                        var in_links = graph.getConnectedLinks(element,{inbound:true})
                        var is_good = true
                        var in_data = []
                        for(var i = 0;i<in_links.length;i++)
                        {
                            var link = in_links[i]
                            var td = temp_data[link.get('source').id]
                            if(td == null)
                            {
                                is_good = false
                                break
                            }
                            in_data[element.get("inPorts").indexOf(link.get('target')["port"])] = td
                        }
                        if(!is_good)
                            continue

                        if(in_links.length != element.get("inPorts").length)
                            continue                        

                        if(temp_data[element.get("id")]!=null)
                            continue                        

                        var data = element.get("data")
                        for(var i = 0;i<in_links.length;i++)
                        {
                            data = data.replace(new RegExp("\\<\\<" + i + "\\>\\>","g"),in_data[i])
                        }
                        temp_data[element.get("id")] = data
                        number_of_changes++
                        if(element.get("name") == "result")
                        {
                            result_saved = true
                            Result = data
                            $("#expressioneditor-expression").html(data)
                            break
                        }

                    }
                    if(result_saved)
                        break;

                    if(number_of_changes == 0)
                        break;
                }

            }

            //console.log("Load time16 " + (new Date() - t) )            

            for(var i = 0;i<LoadLinks.length;i++)
            {
                var link = new joint.dia.Link(LoadLinks[i]);
                graph.addCell(link)
            }

            //console.log("Load time17 " + (new Date() - t) )            

            UpdateResult()

            //console.log("Load time18 " + (new Date() - t) )            


            graph.on('change', UpdateResult)
            graph.on('add', function(){UpdateResult();UpdatePorts();})
            graph.on('remove', UpdateResult)

            //console.log("Load time19 " + (new Date() - t) )            


            var self = this
            $( window ).resize(function() {
                self.UpdatePosition()
            });
            tr()
            
            //console.log("Load time " + (new Date() - t) )
        }
