function setupEventSubscription() {
    const rpmFilter = "readyplayerme";
    const frameReadyEvent = "v1.frame.ready";
    const message = "message";
    window.removeEventListener(message, subscribe);
    document.removeEventListener(message, subscribe);
    window.addEventListener(message, subscribe);
    document.addEventListener(message, subscribe);

    function subscribe(event) {
        const json = parse(event);
        if (json?.source !== rpmFilter || json?.eventName == null) {
            return;
        }

        window.ue.rpmlinkobject.eventreceived(event.data);

        // Subscribe to all events sent from Ready Player Me once frame is ready
        if (json.eventName === frameReadyEvent) {
            if (window) {
                window.postMessage(
                    JSON.stringify({
                        target: rpmFilter,
                        type: "subscribe",
                        eventName: "v1.**",
                    }),
                    "*"
                );
            }
        }
    }

    function parse(event) {
        try {
            return JSON.parse(event.data);
        } catch (error) {
            return null;
        }
    }
}

setupEventSubscription();