import NB from "react-bootstrap/Navbar"
import Nav from "react-bootstrap/Nav"
import { To, useNavigate } from "react-router-dom";
import { useSelector } from "react-redux";
import { State } from "../store";

const Navbar = () => {
    const user = useSelector((state: State) => state.sign)
    const navigate = useNavigate()
    const handleNavLink = (selectedKey: String | null) => {
        if (selectedKey === null)
            return
        navigate(selectedKey as To)
    }

    return (
        <NB>
            <NB.Brand onClick={() => { handleNavLink("/") }}>M.A.L.</NB.Brand>
            <Nav className="ms-auto" activeKey="/" onSelect={handleNavLink}>
                {(!user)
                    &&
                    <>
                        <Nav.Item>
                            <Nav.Link eventKey="/signIn">SignIn</Nav.Link>
                        </Nav.Item>
                        <Nav.Item>
                            <Nav.Link eventKey="/signUp">SignUp</Nav.Link>
                        </Nav.Item>
                    </>
                }
                {
                    user
                    &&
                    <>
                        <Nav.Item>
                            <Nav.Link eventKey="/listDevices">Devices</Nav.Link>
                        </Nav.Item>
                        <Nav.Item>
                            <Nav.Link eventKey="/profile">Profile</Nav.Link>
                        </Nav.Item>
                        <Nav.Item>
                            <Nav.Link eventKey="/signOut">SignOut</Nav.Link>
                        </Nav.Item>
                    </>
                }
            </Nav>
        </NB>
    )
}

export default Navbar;