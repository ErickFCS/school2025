import "./index.css";
import App from "./App";
import { StrictMode } from "react";
import { hydrateRoot } from "react-dom/client";


hydrateRoot(
  document.getElementById("root") as HTMLElement,
  <StrictMode>
      <App />
  </StrictMode>
);
