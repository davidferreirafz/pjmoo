var type_search = "pjmoo";
var anterior_type_search = type_search;


function iniciarBarra()
{

    return;
}

function setSearchType(searchType)
{
    switch(searchType){
        case 'jogosdaqui':
            type_searc='jogosdaqui';
            break;
        case 'GameDev-PT':
            type_search='gamedev-pt';
            break;
        case 'OpenGL Brasil':
            type_search='openglbrasil';
            break;       
        case 'Gamedev':
            type_search='gamedev';
            break;    
        case 'Google':
            type_search='google';
            break;
        case 'Clear':
            anterior_type_search = type_search;
            type_search='clear';
            break;
        case 'Unidev':            
            type_search='unidev';
            break;          
        case 'Codigo Livre':                        
            type_search='codigolivre';
            break;                   
        case 'PJMOO':            
        default:
            type_search='pjmoo';
            break;
    }
}

function Search(event)
{
    if(type_search != 'clear') {

        var critBox = document.getElementById("chave_busca");
        var chave = critBox.value;
        var url_busca;
        
        if(chave == '') {
            alert("Entre com o texto a ser procurado");
            return;
        }

        if (type_search == 'pjmoo'){
            url_busca = 'http://pjmoo.codigolivre.org.br/wiki/index.php/Especial:Search?search='+chave+'&go=vai';
        } else if (type_search == 'unidev'){
            url_busca = 'http://www.unidev.com.br/busca.asp?busca=' + chave;
        } else if (type_search == 'google'){
            url_busca = 'http://www.google.com.br/search?q=' + chave;
        } else if (type_search == 'gamedev') {
            url_busca = 'http://www.google.com/custom?hl=en&oe=ISO-8859-1&client=pub-3167291168602081&cof=FORID%3A1%3BL%3Ahttp%3A%2F%2Fimages.gamedev.net%2Fsitelogo.gif%3BLH%3A50%3BLW%3A225%3BGL%3A1%3BBGC%3AFFFFFF%3BT%3A%23000000%3BLC%3A%233366cc%3BVLC%3A%233366cc%3BALC%3A%233366ff%3BGALT%3A%23339966%3BGFNT%3A%23808080%3BGIMP%3A%23008000%3BDIV%3A%233366CC%3BLBGC%3AFFFFFF%3BAH%3Acenter%3BS%3Ahttp%3A%2F%2Fwww.gamedev.net%3B&domains=GameDev.net&q=' + chave+'&btnG=Search&sitesearch=GameDev.net';
        } else if (type_search == 'openglbrasil'){
            url_busca = 'http://www.opengl.com.br/modules.php?op=modload&name=Recherches&file=index&query=' + chave;
        } else if (type_search == 'codigolivre'){
            url_busca = 'http://codigolivre.org.br/search/?type_of_search=soft&group_id=1187&words=' + chave;
        } else if (type_search == 'gamedev-pt'){
            url_busca = 'http://www.gamedev-pt.net/modules.php?name=Search&query=' + chave;
        } else if (type_search == 'jogosdaqui'){
            url_busca = 'http://www.jogosdaqui.com.br/index.php?p=cl&t=search&query=' + chave;
        }

        irSite(url_busca);
        addtoSearchHistory(chave);

    } else {
        type_search = 'unidev';
    }
}

function irSite(siteURL)
{
    window._content.document.location = siteURL;
}

function CriteriaSelect(event)
{
    var critBox = document.getElementById("chave_busca");
    var ePt = critBox.inputField.textLength;
    var curClickStart = critBox.inputField.selectionStart;
    var curClickEnd = critBox.inputField.selectionEnd;
    var curSelSize = curClickEnd - curClickStart;

    if (event && ePt > 0) {
        switch(event.type) {

        case "dblclick":
            if (!boolCritSelected) {
                critBox.inputField.select();
                boolCritSelected = true;
            }
            else {
                critBox.inputField.setSelectionRange(curClickStart, curClickEnd);
                boolCritSelected = false;
            }
            break;

        case "focus":
            if (critIgnoreFocus) {
                critIgnoreFocus = false;
            }
            else {
                if (boolCritSelected) {
                    if (hkeytgl) {
                        critBox.inputField.setSelectionRange(0, 0 );
                        boolCritSelected = false;
                    }
                    else {
                        critBox.inputField.select();
                    }
                }
                else {
                    critBox.inputField.select();
                    boolCritSelected = true;
                }
            }
            break;

        case "mousedown":
            if (critBox.getAttribute("focused")) {
                critIgnoreClick = true;
            }
            else {
                critIgnoreFocus = true;
                critIgnoreClick = false;
                critBox.inputField.setSelectionRange(0, 0 );
                boolCritSelected = true;
            }
            break;

        case "click":
            if (!critIgnoreClick && curSelSize == 0) {
                critBox.inputField.select();
                boolCritSelected = true;
            }
            break;

        default:
            break;

        }
    } // no event or text
}

function addtoSearchHistory(term)
{
    // This function adds the string "term" to the search
    // history *only* if it is not already there
    var critBox = document.getElementById("chave_busca");
    var historyMenu = critBox.childNodes.item(0);

    var numHistItems = historyMenu.childNodes.length;
    var alreadyInHist = false;
    var i = 0;

    // iterate over the current history and check if the term is
    // already there
    for (i = 0; i < numHistItems; i++) {
        if (term == historyMenu.childNodes[i].getAttribute("label")) {
            alreadyInHist = true;
        }
    }

    // add to history
    if (!alreadyInHist) {
        var myMenuItem = document.createElement("menuitem");
        myMenuItem.setAttribute("label", term);

        if (numHistItems <= 0) {
            historyMenu.appendChild(myMenuItem);
        }
        else {
            historyMenu.insertBefore(myMenuItem, historyMenu.childNodes[0]);
        }

        numHistItems++;

        // if too many items have been added then remove extra items from the bottom
        if (numHistItems > maxHistCnt) {
            var numToRemove = numHistItems - maxHistCnt;

            // iterate over the current history and remove any extraneous items
            for (i = 1; i <= numToRemove; i++) {
                historyMenu.removeChild(historyMenu.lastChild);
            }
        }
    }
}

function clearSearchHistory()
{
    // This function removes all items from the search
    // history (both history pref and popup menu)
    var critBox = document.getElementById("chave_busca");

    // If called from the prefs, we need to get the main document
    // first.
    if (!critBox) {
      mainDoc = top.opener.document;
      critBox = mainDoc.getElementById("chave_busca");
    }
    if (!critBox)
      alert("Sorry!! :(");

    var historyMenu = critBox.childNodes.item(0);
    var numHistItems = historyMenu.childNodes.length;


    // iterate over the current history and remove each item
    for (var i = numHistItems - 1; i >= 0; i--) {
        historyMenu.removeChild(historyMenu.childNodes[i]);
    }

    // next clear all the term buttons, the input field
    // (by setting selected index to -1), and history pref

    critBox.selectedIndex = -1;

}


function showHide() 
{
    var bar=document.getElementById("games_toolsbr-main");
    var btnShow=document.getElementById("btn_obShow");
    bar.setAttribute("collapsed",!bar.collapsed);
    btnShow.setAttribute("collapsed",!btnShow.collapsed);
}
