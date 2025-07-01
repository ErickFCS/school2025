import Container from "react-bootstrap/Container";
import Spinner from "react-bootstrap/Spinner";


const LoadingSpinner = () => {
    return (
        < Container style={{ alignItems: "center", display: "grid", flexGrow: 1, gridTemplate: "repeat(3, 1fr) / repeat(3, 1fr)", justifyItems: "center" }
        }>
            <Spinner animation="border" role="status" style={{ gridColumn: "2", gridRow: "2" }}>
                <span className="visually-hidden">Loading...</span>
            </Spinner>
        </Container >
    );
};

export default LoadingSpinner;
