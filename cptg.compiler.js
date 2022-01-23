const cptg = {
    supportedTags: [ "var", "const", "seq", "br" ],
    varTypes: {
        Char: "Char",
        String: "String",
        Number: "Number",
        Float: "Float",
    },

    rangeTypes: {
        abc: "abc",
        ABC: "ABC",
        special: "special",
        all: "all"    
    },


    runCompilation: ( data ) => {
        try {
            const parsedXML = cptg.parseXML( data )
            const tokens = cptg.tokenize( parsedXML )
            const translated = cptg.translateTokens( tokens )
            return translated
        } catch(err) {
            throw err
            return
        }
    },

    parseXML: ( data ) => {
        const parser = new DOMParser()
        const doc = parser.parseFromString( data, "application/xml" );
        const errorNode = doc.querySelector("parsererror");
        if (errorNode) {
            throw errorNode // console.log("error while parsing");
            return
        } 
        return doc.getElementsByTagName("test")[0].childNodes
    },

    tokenize: ( childNodes ) => {
        let tokenQueue = []
        childNodes.forEach( node => {
            if ( !utils.equalToAny(node.nodeName, cptg.supportedTags) ) return;
            tokenQueue.push( cptg["parse"+node.nodeName]( node ) )
        })
        return tokenQueue
    },

    parsevar: ( data ) => {
        return {
            token: "var",
            parameters: {
                type: data.getAttribute('type') ?? cptg.varTypes.Number,
                range: data.getAttribute('range') ?? "0:9",
                length: Number(data.getAttribute('length')) ?? 3, // string only
            }
        }
    },

    parseconst: ( data ) => {
        return {
            token: "const",
            parameters: {
                value: data.getAttribute('value') ?? 0,
            }
        }
    },

    parseseq: ( data ) => {
        return {
            token: "seq",
            parameters: {
                times: Number(data.getAttribute('times')) ?? 1,
                insideNodes: data.childNodes,
            }
        }
    },

    parsebr: ( data ) => {
        return {
            token: "br",
        }
    },

    translateTokens: ( tokens ) => {
        let finalOutput = ""
        tokens.map( token => {
            finalOutput += cptg["translate"+token.token]( token ) + " "
        })
        return finalOutput
    },

    translatevar: ( data ) => {
        let output = vartranslator["translate"+data.parameters.type]( data )
        return output
    },

    translateconst: ( data ) => {
        return data.parameters.value
    },

    translatebr: ( data ) => {
        return "</br>"
    },

    translateseq: ( data ) => {
        if ( data.parameters.insideNodes.length > 0 ) {
            let output = ""
            for ( let i = 0; i<data.parameters.times; i++ ) {
                const tokenized = cptg.tokenize( data.parameters.insideNodes )
                const translated = cptg.translateTokens( tokenized )
                output += translated
            }
            return output
        }
        return ""
    },

}

const vartranslator = {
    upperCharacters: "QWERTYUIOPASDFGHJKLZXCVBNM".split(""),
    lowerCharacters: "qwertyuiopasdfghjklzxcvbnm".split(""),
    specialCharacters: `! @ # $ % ^ & * ( ) - _ + = { } [ ] : ; " ' < > , . ? / | \ ~`.split(' '),

    translateChar: ( token ) => {
        switch( token.parameters.range ) {
            case cptg.rangeTypes.all:
                let c1 = utils.randomElement( vartranslator.upperCharacters )
                let c2 = utils.randomElement( vartranslator.lowerCharacters )
                let c3 = utils.randomElement( vartranslator.specialCharacters )
                return utils.randomElement( [c1,c2,c3] )
                break;
            case cptg.rangeTypes.ABC:
                return utils.randomElement( vartranslator.upperCharacters )
                break;
            case cptg.rangeTypes.special:
                return utils.randomElement( vartranslator.specialCharacters )
                break;
            default: // abc
                return utils.randomElement( vartranslator.lowerCharacters )
                break;
        }
    }, 

    translateNumber: ( token ) => {
        let range = token.parameters.range.split(":").map( e => Number(e) | 0 )
        range = range.length == 2 ? range : [0,1]
        range = range.sort()
        return Math.round(range[0] + Math.random()*( range[1] - range[0] )).toString()
    },

    translateFloat: ( token ) => {
        let range = token.parameters.range.split(":").map( e => Number(e) | 0 )
        range = range.length == 2 ? range : [0,1]
        range = range.sort()
        return (range[0] + Math.random()*( range[1] - range[0] )).toString().slice(0, 2+token.parameters.length )
    },

    translateString: ( token ) => {
        let output = ""
        for ( let i = 0; i<token.parameters.length; i++ )
            output += vartranslator.translateChar( token )
        return output
    },

}


const utils = {
    includesAny: (str, strings) => {
        check=false;
        strings.map( e => { if ( str.includes(e) ) check=true })
        return check
    },
    equalToAny: (str, strings) => {
        check=false;
        strings.map( e => { if ( str === e ) check=true })
        return check
    },

    randomElement: ( arr ) => {
        return arr[ Math.floor(Math.random()*arr.length) ]
    },
}