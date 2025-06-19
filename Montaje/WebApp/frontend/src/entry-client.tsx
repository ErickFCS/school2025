import App from "./App";
import { hydrateRoot } from "react-dom/client";
import { BrowserRouter as Router } from "react-router-dom"
import { Provider } from 'react-redux'
import store from "./store";


hydrateRoot(
    document.getElementById("root") as HTMLElement,
    <Provider store={store}>
        <Router>
            <App />
        </Router >
    </Provider>
);
