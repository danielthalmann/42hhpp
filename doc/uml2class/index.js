fs = require('fs');
var parser = require('xml2json');

const logfile = "out/extract.log";

var umlClasses = [];

fs.readFile( '../architecture_tpm.drawio', function(err, data) {
    var json = JSON.parse(parser.toJson(data));
    var cell = json.mxfile.diagram.mxGraphModel.root.mxCell;

    filestrem.write("");

    cell.forEach(element => {
    
        if (element.parent == 1 && element.vertex == 1) {
            
            filestrem.append( element.value + "\n");

            let newClass = {
                "name" : element.value,
                "properties" : []
            };

            cell.forEach(childElement => {

                if (childElement.parent == element.id && childElement.value != "" && childElement.value != "\n") {

                    let property = {
                        "access" : childElement.value.trim()[0],
                        "type" : "",
                        "name" : ""
                    };

                    keyval = childElement.value.substring(2).split(":");

                    property.name = keyval[0].trim();
                    property.type = keyval[1].trim();

                    filestrem.append(childElement.value.substring(2) + "\n");

                    newClass.properties.push(property);

                }

            });

            umlClasses.push(newClass);

        }      

    });


    umlClasses.forEach(cl => {
        
        var fname = "out/" + cl.name + ".hpp";
        var content = "";
        
        content += "#ifndef " + cl.name.toUpperCase() + "_HPP\n" 
                +  "#define " + cl.name.toUpperCase() + "_HPP\n" 
                +  "\n\nclass " + cl.name + "\n{";
        
        content += "\n\npublic:\n\n"

        cl.properties.forEach(pr => {           
            if (pr.access == "+") {
                content += "\t" + pr.type + " " + pr.name+ ";\n"                
            }         
        });

        content += "\n\nprivate:\n\n"

        cl.properties.forEach(pr => {           
            if (pr.access == "-") {
                content += "\t" + pr.type + " " + pr.name+ ";\n"                
            }         
        });

        content += "\n\n};" 
                +  "\n\n#endif\n";
        
        filestrem.write(content, fname);
    });


});


var filestrem = {

    "write": function (s, filename)
    {
        if (typeof(filename) == "undefined")
            filename = logfile;

        fs.writeFile(filename, s,
        {
        encoding: "utf8",
        flag: "w"
        }, (err) => { } );
    },
    
    "append" : function(s, filename)
    {
        if (typeof(filename) == "undefined")
            filename = logfile;

        fs.writeFile(filename, s,
        {
        encoding: "utf8",
        flag: "a"
        }, (err) => {} );
    }
}
