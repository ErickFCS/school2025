import "./App.css";
import "../../node_modules/bootstrap/dist/css/bootstrap.min.css";
import "../../node_modules/bootstrap/dist/js/bootstrap.bundle.js";
import Navbar from "./components/Navbar.js";
import Notification from "./components/Notification.js";
import EditPage from "./components/pages/Edit.js";
import IndexPage from "./components/pages/Index.js";
import InfoPage from "./components/pages/Info.js";
import ListDevicesPage from "./components/pages/ListDevices.js";
import ProfilePage from "./components/pages/Profile.js";
import SignInPage from "./components/pages/SignIn.js";
import SignOut from "./components/pages/SignOut.js";
import SignUpPage from "./components/pages/SignUp.js";
import Stack from "react-bootstrap/Stack"
import { Route, Routes } from "react-router-dom";


function App() {
    return (
        <Stack gap={2} style={{ minHeight: "100dvh" }}>
            <Navbar />
            <br style={{ height: "10%" }} />
            <Notification />
            <br style={{ height: "10%" }} />
            <Routes>
                <Route path="/" element={<IndexPage />} />
                <Route path="/signIn" element={<SignInPage />} />
                <Route path="/signUp" element={<SignUpPage />} />
                <Route path="/signOut" element={<SignOut />} />
                <Route path="/profile" element={<ProfilePage />} />
                <Route path="/listDevices" element={<ListDevicesPage />} />
                <Route path="/info/:device" element={<InfoPage />} />
                <Route path="/edit/:device" element={<EditPage />} />
            </Routes>
        </Stack >
    );
}

export default App;
