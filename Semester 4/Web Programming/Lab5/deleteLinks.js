function deleteLinks() {
    var links = document.getElementsByTagName("a");
    var validLinks = [];
    for (var i = links.length - 1; i >= 0; i--) {
        var href = links[i].href;
        if (href.startsWith("http://www.scs.ubbcluj.ro") || href.startsWith("https://www.scs.ubbcluj.ro")) {
           validLinks.push(links[i]);
           links[i].parentNode.parentNode.removeChild(links[i].parentNode);
        }
    }

    validLinks.sort(function(a, b){
        return a.textContent.localeCompare(b.textContent);
    });
    var container = document.getElementById('links-container');
    if (!container) {
        console.log('Container not found for reinserting links');
        return;
    }
    container.innerHTML = '';
    validLinks.forEach(function(link) {
        var wrapper = document.createElement('div');
        wrapper.appendChild(link);
        container.appendChild(wrapper);
    });
}
