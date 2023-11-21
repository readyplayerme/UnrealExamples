// Copyright © 2021++ Ready Player Me

#pragma once

static char* RPM_SETUP_JAVASCRIPT = R"(
function SetupEventSubscription() {
	const rpmFilter = "readyplayerme";
	const frameReadyEvent = "v1.frame.ready";
	const message = "message";
	window.removeEventListener(message, Subscribe);
	document.removeEventListener(message, Subscribe);
	window.addEventListener(message, Subscribe);
	document.addEventListener(message, Subscribe);

	function Subscribe(event) {
		const json = Parse(event);
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

	function Parse(event) {
		try {
			return JSON.parse(event.data);
		} catch (error) {
			return null;
		}
	}
}

SetupEventSubscription();
)";
