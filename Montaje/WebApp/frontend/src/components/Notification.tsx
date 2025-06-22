import Alert from "react-bootstrap/Alert"
import { useSelector } from "react-redux";
import { State } from "../store";


const Notification = () => {
    const notifications = useSelector((state: State) => state.notification.notifications)

    return (
        <>
            {Object.values(notifications).map(({ message, variant }) => {
                return (
                    <Alert variant={variant} className="text-center" >
                        {message}
                    </Alert >
                )
            })}
        </>
    );
}

export default Notification;