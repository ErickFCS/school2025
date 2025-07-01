import App from "./App";
import store from "./store";
import { hydrateRoot } from "react-dom/client";
import { Provider } from "react-redux";
import { BrowserRouter as Router } from "react-router-dom";


hydrateRoot(
    document.getElementById("root") as HTMLElement,
    <Provider store={store}>
        <Router>
            <App />
        </Router >
    </Provider>
);
