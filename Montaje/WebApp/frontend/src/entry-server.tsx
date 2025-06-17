import App from "./App";
import { renderToString } from "react-dom/server";


export function render(_url: string) {
    const html = renderToString(
            <App />
    );
    return { html };
}
