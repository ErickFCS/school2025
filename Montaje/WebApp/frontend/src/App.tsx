import "./App.css";
import "../../node_modules/bootstrap/dist/css/bootstrap.min.css";
import "../../node_modules/bootstrap/dist/js/bootstrap.bundle.js";
import Stack from "react-bootstrap/Stack"
import { Route, Routes } from "react-router-dom";
import Navbar from "./components/Navbar.js";

function App() {
    return (
        <Stack gap={2}>
            <Navbar />
            <Routes>
                <Route path="/" element={<p>index</p>} />
                <Route path="/signIn" element={<p>signIn</p>} />
                <Route path="/signUp" element={<p>signUp</p>} />
                <Route path="/profile" element={<p>profile</p>} />
                <Route path="/listDevices" element={<p>listDevices</p>} />
                <Route path="/info/:device" element={<p>info</p>} />
                <Route path="/edit" element={<p>edit</p>} />
            </Routes>
        </Stack >
    );
}

export default App;
