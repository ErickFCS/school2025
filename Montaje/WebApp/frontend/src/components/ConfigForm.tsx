import { deleteConfig, updateOrCreateConfig } from "../reducers/devices";
import { GenericConfigSchema } from "../types/configs";
import { useFormik } from "formik";
import Button from "react-bootstrap/Button";
import Form from "react-bootstrap/Form";
import { useDispatch } from "react-redux";


const ConfigForm = ({ config, espId }: { config: GenericConfigSchema | undefined, espId: number }) => {
    const dispatch = useDispatch();

    const formik = useFormik({
        initialValues: {
            field: config?.field || "",
            value: config?.value || ""
        },
        onSubmit(values) {
            dispatch(updateOrCreateConfig({
                ...config,
                espId,
                field: values.field,
                value: values.value
            }));
            formik.resetForm({ values });
        }
    });

    const handleDelete = () => {
        if (config?.id) {
            dispatch(deleteConfig(config.id));
        }
    };

    return (
        <Form onSubmit={formik.handleSubmit} onReset={formik.handleReset}>
            <Form.Group>
                <Form.Label>Field</Form.Label>
                <Form.Control name="field" value={formik.values.field} onChange={formik.handleChange} />
            </Form.Group>
            <Form.Group>
                <Form.Label>Value</Form.Label>
                <Form.Control name="value" value={formik.values.value} onChange={formik.handleChange} />
            </Form.Group>
            {config?.id &&
                <Form.Group>
                    <Button variant="danger" onClick={handleDelete}>X</Button>
                </Form.Group>
            }
            {formik.dirty &&
                <>
                    <Form.Group>
                        <Button variant="success" type="submit">Update or Create</Button>
                    </Form.Group>
                    <Form.Group>
                        <Button variant="info" type="reset">Reset</Button>
                    </Form.Group>
                </>
            }
        </Form>
    );
};

export default ConfigForm;
