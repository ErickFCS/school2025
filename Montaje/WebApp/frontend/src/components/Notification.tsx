import { State } from "../store";
import Alert from "react-bootstrap/Alert";
import { useSelector } from "react-redux";


const Notification = () => {
    const notifications = useSelector((state: State) => state.notification.notifications);

    return (
        <>
            {Object.values(notifications).map(({ message, variant }, i) => {
                return (
                    <Alert key={`alert${i}`} variant={variant} className="text-center" >
                        {message}
                    </Alert >
                );
            })}
        </>
    );
};

export default Notification;
