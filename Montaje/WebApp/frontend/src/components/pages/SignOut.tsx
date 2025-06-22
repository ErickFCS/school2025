import { useDispatch } from "react-redux"
import { signOut } from "../../reducers/sign"
import { useNavigate } from "react-router-dom"
import { useEffect } from "react"
import Container from "react-bootstrap/Container"
import Spinner from "react-bootstrap/Spinner"


const SignOut = () => {
    const dispatch = useDispatch()
    const navigate = useNavigate()
    
    useEffect(() => {
        dispatch(signOut())
        navigate("/", { replace: true });

    }, [dispatch, navigate])

    return (
        <Container style={{ display: "grid", gridTemplate: "repeat(3, 1fr) / repeat(3, 1fr)", justifyItems: "center", alignItems: "center", flexGrow: 1 }}>
            <Spinner animation="border" role="status" style={{ gridRow: "2", gridColumn: "2" }}>
                <span className="visually-hidden">Loading...</span>
            </Spinner>
        </Container>
    )
}

export default SignOut;