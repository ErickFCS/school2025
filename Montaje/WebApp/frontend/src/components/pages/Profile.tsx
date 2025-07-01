import { State } from "../../store";
import Card from "react-bootstrap/Card";
import { useSelector } from "react-redux";
import { useNavigate } from "react-router-dom";


const ProfilePage = () => {
    const user = useSelector((state: State) => state.sign.user);
    const navigate = useNavigate();
    if (!user) {
        navigate("/signOut", { replace: true });
        return null;
    }
    return (
        <Card>
            <Card.Header as="h5">{user?.username}</Card.Header>
            <Card.Body>
                <Card.Text>
                    Some info
                </Card.Text>
            </Card.Body>
        </Card>
    );
};

export default ProfilePage;
