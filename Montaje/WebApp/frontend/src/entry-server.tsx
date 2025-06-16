import App from "./App";
import { StrictMode } from "react";
import { renderToString } from "react-dom/server";


export function render(_url: string) {
    const html = renderToString(
        <StrictMode>
            <App />
        </StrictMode>
    );
    return { html };
}
