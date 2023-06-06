window.ue.rpmlinkobject.eventReceived("TEST");

window.addEventListener('message', function(event)
    { 
        window.ue.rpmlinkobject.avatargenerated(event.data);
        window.ue.rpmlinkobject.eventReceived("TEST");
    });