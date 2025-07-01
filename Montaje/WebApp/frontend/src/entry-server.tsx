import App from "./App";
import { renderToString } from "react-dom/server";
import { BrowserRouter as Router } from "react-router-dom";


// eslint-disable-next-line no-unused-vars
export function render(_url: string) {
    const html = renderToString(
        <Router>
            <App />
        </Router>
    );
    return { html };
}
